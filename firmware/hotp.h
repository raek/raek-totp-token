#pragma once

#include <stddef.h>
#include <stdint.h>

#include "hmac_sha1.h"

#define HOTP_COUNTER_BYTES 8
#define HOTP_DIGITS 6

typedef struct {
    uint8_t counter_bytes[HOTP_COUNTER_BYTES];
    HmacSha1 hmac_sha1_scratchpad;
    uint8_t hmac_sha1_code[HMAC_SHA1_CODE_BYTES];
} Hotp;

void hotp(Hotp *scratchpad, uint8_t *secret, size_t secret_length, uint64_t counter, char *digits_output);
