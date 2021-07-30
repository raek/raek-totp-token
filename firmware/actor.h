#pragma once

#include <stddef.h>

#define ACTOR_INVALID_SIG -1

struct actor;

typedef int actor_sig;

typedef void (*actor_dispatcher)(struct actor *actor, actor_sig sig);

struct actor {
    actor_dispatcher dispatcher;
};

void actor_init(struct actor *actor, actor_dispatcher dispatcher);
void actor_post(struct actor *recipient, actor_sig sig);
