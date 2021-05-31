#pragma once

#include <stddef.h>
#include <stdint.h>

#define SHA1_DIGEST_BYTES 20
#define SHA1_DIGEST_WORDS 5
#define SHA1_BLOCK_BYTES 64
#define SHA1_MESSAGE_WORDS 80

typedef struct {
    uint64_t total_length;
    uint8_t block[SHA1_BLOCK_BYTES];
    uint32_t w[SHA1_MESSAGE_WORDS];
    size_t pos;
    uint32_t h[SHA1_DIGEST_WORDS];
} Sha1;

void sha1_init(Sha1 *sha1);
void sha1_update(Sha1 *sha1, const uint8_t *data, size_t length);
void sha1_digest(Sha1 *sha1, uint8_t *digest);
