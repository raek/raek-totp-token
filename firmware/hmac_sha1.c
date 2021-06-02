#include <string.h>

#include "hmac_sha1.h"

#define HMAC_INNER_PAD_BYTE 0x36
#define HMAC_OUTER_PAD_BYTE 0x5c

static inline void xor_bytes(uint8_t *data, size_t data_length, uint8_t xor_value);

void hmac_sha1(HmacSha1 *scratchpad, const uint8_t *key, size_t key_length, const uint8_t *message, size_t message_length, uint8_t *code_output)
{
    memset(scratchpad->key_block, 0, SHA1_BLOCK_BYTES);
    if (key_length <= SHA1_BLOCK_BYTES) {
        // K0 = K || 00...00
        memcpy(scratchpad->key_block, key, key_length);
    } else {
        // K0 = H(K) || 00...00
        sha1_init(&scratchpad->sha1);
        sha1_update(&scratchpad->sha1, key, key_length);
        sha1_digest(&scratchpad->sha1, scratchpad->key_block);
    }
    // inner_digest = H((K0 (+) ipad) || message)
    sha1_init(&scratchpad->sha1);
    xor_bytes(scratchpad->key_block, SHA1_BLOCK_BYTES, HMAC_INNER_PAD_BYTE);
    sha1_update(&scratchpad->sha1, scratchpad->key_block, SHA1_BLOCK_BYTES);
    sha1_update(&scratchpad->sha1, message, message_length);
    sha1_digest(&scratchpad->sha1, scratchpad->inner_digest);
    // code = H((K0 (+) opad) || inner_digest)
    sha1_init(&scratchpad->sha1);
    xor_bytes(scratchpad->key_block, SHA1_BLOCK_BYTES, HMAC_INNER_PAD_BYTE ^ HMAC_OUTER_PAD_BYTE);
    sha1_update(&scratchpad->sha1, scratchpad->key_block, SHA1_BLOCK_BYTES);
    sha1_update(&scratchpad->sha1, scratchpad->inner_digest, SHA1_DIGEST_BYTES);
    sha1_digest(&scratchpad->sha1, code_output);
}

static inline void xor_bytes(uint8_t *data, size_t length, uint8_t xor_value)
{
    for (size_t i = 0; i < length; i++) {
        data[i] ^= xor_value;
    }
}
