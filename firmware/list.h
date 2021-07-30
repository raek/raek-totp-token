#pragma once

// This is a stripped-down version of <linux/list.h>

#define POISON_POINTER_DELTA 0
#define LIST_POISON1  ((void *) 0x100 + POISON_POINTER_DELTA)
#define LIST_POISON2  ((void *) 0x122 + POISON_POINTER_DELTA)

#define container_of(ptr, type, member) ({				\
            void *__mptr = (void *)(ptr);                               \
            ((type *)(__mptr - offsetof(type, member)));                \
        })

struct list_head {
    struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
    __list_add(new, head->prev, head);
}

static inline void __list_del(struct list_head * prev, struct list_head * next)
{
    next->prev = prev;
    prev->next = next;
}

static inline void __list_del_entry(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
}

static inline void list_del(struct list_head *entry)
{
    __list_del_entry(entry);
    entry->next = LIST_POISON1;
    entry->prev = LIST_POISON2;
}

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_first_entry_or_null(ptr, type, member) ({                  \
            struct list_head *head__ = (ptr);                           \
            struct list_head *pos__ = head__->next;                     \
            pos__ != head__ ? list_entry(pos__, type, member) : NULL;   \
        })
