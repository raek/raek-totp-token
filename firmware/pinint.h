#pragma once

#include "actor.h"

struct pinint;

void pinint_acquire(struct pinint *pinint, struct actor *recipient, actor_sig rising_sig, actor_sig falling_sig);
