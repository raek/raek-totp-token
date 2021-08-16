#include <stddef.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>

#include "actor.h"
#include "actor_avr.h"
#include "halt.h"
#include "list.h"
#include "result.h"

#define MSG_QUEUE_SIZE 10

struct msg {
    struct list_head list;
    struct actor *recipient;
    actor_sig sig;
};

static struct list_head free_msgs;
static struct list_head incoming_msgs;

static struct msg msg_storage[MSG_QUEUE_SIZE];

static inline void post(struct actor *recipient, actor_sig sig);
static inline struct msg *pop_msg(struct list_head *list);
static inline void push_msg(struct list_head *list, struct msg *msg);

void actor_system_init(void)
{
    INIT_LIST_HEAD(&free_msgs);
    INIT_LIST_HEAD(&incoming_msgs);
    for (int i = 0; i < MSG_QUEUE_SIZE; i++) {
        list_add_tail(&msg_storage[i].list, &free_msgs);
    }
}

void actor_init(struct actor *actor, actor_dispatcher dispatcher)
{
    actor->dispatcher = dispatcher;
}

void actor_post(struct actor *recipient, actor_sig sig)
{
    cli();
    post(recipient, sig);
    sei();
}

void actor_post_from_isr(struct actor *recipient, actor_sig sig)
{
    post(recipient, sig);
}

static inline void post(struct actor *recipient, actor_sig sig)
{
    struct msg *msg = pop_msg(&free_msgs);
    if (msg == NULL) {
        (void) ERROR("No free messages left.");
        halt();
    } else {
        msg->recipient = recipient;
        msg->sig = sig;
        push_msg(&incoming_msgs, msg);
    }
}

void actor_system_loop(void)
{
    DDRC |= (1<<7);
    PORTC |= (1<<7);
    for (;;) {
        cli();
        struct msg *msg = pop_msg(&incoming_msgs);
        if (msg == NULL) {
            set_sleep_mode(SLEEP_MODE_IDLE);
            sleep_enable();
            PORTC &= ~(1<<7);
            sei();
            sleep_cpu();
            PORTC |= (1<<7);
            continue;
        }
        struct actor *recipient = msg->recipient;
        actor_sig sig = msg->sig;
        push_msg(&free_msgs, msg);
        sei();
        enum result result = recipient->dispatcher(recipient, sig);
        if (result != RESULT_OK) {
            halt();
        }
    }
}

static inline struct msg *pop_msg(struct list_head *list)
{
    struct msg *msg = list_first_entry_or_null(list, struct msg, list);
    if (msg != NULL) {
        list_del(&msg->list);
    }
    return msg;
}

static inline void push_msg(struct list_head *list, struct msg *msg)
{
    list_add_tail(&msg->list, list);
}
