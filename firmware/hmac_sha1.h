#pragma once

#include <stddef.h>
#include <stdint.h>

#include "sha1.h"

#define HMAC_SHA1_CODE_BYTES SHA1_DIGEST_BYTES

typedef struct {
    uint8_t key_block[SHA1_BLOCK_BYTES];
    Sha1 sha1;
    uint8_t inner_digest[SHA1_DIGEST_BYTES];
} HmacSha1;

void hmac_sha1(HmacSha1 *scratchpad, const uint8_t *key, size_t key_length, const uint8_t *message, size_t message_length, uint8_t *code_output);
