#pragma once

#include <stddef.h>
#include <stdint.h>

#include "hmac_sha1.h"

#define HOTP_COUNTER_BYTES 8
#define HOTP_DIGITS 6

struct hotp {
    uint8_t counter_bytes[HOTP_COUNTER_BYTES];
    struct hmac_sha1 hmac_sha1_scratchpad;
    uint8_t hmac_sha1_code[HMAC_SHA1_CODE_BYTES];
};

void hotp(struct hotp *scratchpad, const uint8_t *secret, size_t secret_length, uint64_t counter, char *digits_output);
