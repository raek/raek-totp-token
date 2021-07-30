#include "actor.h"

void actor_init(struct actor *actor, actor_dispatcher dispatcher)
{
    actor->dispatcher = dispatcher;
}

void actor_post(struct actor *recipient, actor_sig sig)
{
    recipient->dispatcher(recipient, sig);
}
