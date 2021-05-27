#pragma once

#include <stddef.h>
#include <stdint.h>

#define SHA1_DIGEST_BYTES 20

typedef struct {
    int dummy;
} Sha1;

void sha1_init(Sha1 *sha1);
void sha1_update(Sha1 *sha1, const uint8_t *data, size_t length);
void sha1_digest(Sha1 *sha1, uint8_t *digest);
