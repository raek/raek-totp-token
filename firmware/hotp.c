#include "hotp.h"

static uint32_t dynamic_truncation(const uint8_t *hash);
static void write_u64be(uint8_t *buffer, uint64_t value);
static uint32_t read_u32be(const uint8_t *buffer);

void hotp(Hotp *scratchpad, uint8_t *secret, size_t secret_length, uint64_t counter, char *digits_output)
{
    write_u64be(scratchpad->counter_bytes, counter);
    hmac_sha1(&scratchpad->hmac_sha1_scratchpad,
              secret, secret_length,
              scratchpad->counter_bytes, HOTP_COUNTER_BYTES,
              scratchpad->hmac_sha1_code);
    uint32_t dt = dynamic_truncation(scratchpad->hmac_sha1_code);
    for (int i = HOTP_DIGITS - 1; i >= 0; i--) {
        digits_output[i] = '0' + (dt % 10);
        dt /= 10;
    }
}

static uint32_t dynamic_truncation(const uint8_t *hash)
{
    size_t offset = hash[HMAC_SHA1_CODE_BYTES-1] & 0x0f;
    return read_u32be(&hash[offset]) & 0x7fffffffUL;
}

static void write_u64be(uint8_t *buffer, uint64_t value)
{
    uint64_t x = value;
    for (int i = 7; i >= 0; i--) {
        buffer[i] = x & 0xffULL;
        x >>= 8;
    }
}

static uint32_t read_u32be(const uint8_t *buffer) {
    uint32_t result = 0;
    for (int i = 0; i < 4; i++) {
        result <<= 8;
        result |= buffer[i];
    }
    return result;
}
