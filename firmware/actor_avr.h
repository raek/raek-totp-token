#pragma once

#include "actor.h"

void actor_post_from_isr(struct actor *recipient, actor_sig sig);
void actor_system_init(void);
void actor_system_loop(void);
