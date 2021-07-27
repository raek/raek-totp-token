#pragma once

#include <stddef.h>
#include <stdint.h>

#include "sha1.h"

#define HMAC_SHA1_CODE_BYTES SHA1_DIGEST_BYTES

struct hmac_sha1 {
    uint8_t key_block[SHA1_BLOCK_BYTES];
    struct sha1 sha1;
    uint8_t inner_digest[SHA1_DIGEST_BYTES];
};

void hmac_sha1(struct hmac_sha1 *scratchpad, const uint8_t *key, size_t key_length, const uint8_t *message, size_t message_length, uint8_t *code_output);
