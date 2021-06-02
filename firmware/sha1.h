#pragma once

#include <stddef.h>
#include <stdint.h>

#define SHA1_DIGEST_BYTES 20
#define SHA1_DIGEST_WORDS 5
#define SHA1_BLOCK_BYTES 64
#define SHA1_BLOCK_WORDS 16

typedef struct {
    uint64_t input_length;
    uint32_t w[SHA1_BLOCK_WORDS];
    size_t pos;
    uint32_t h[SHA1_DIGEST_WORDS];
} Sha1;

void sha1_init(Sha1 *sha1);
void sha1_update(Sha1 *sha1, const uint8_t *data, size_t length);
void sha1_digest(Sha1 *sha1, uint8_t *digest);
