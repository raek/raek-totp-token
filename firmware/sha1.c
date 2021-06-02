#include <string.h>

#ifdef SHA1_DEBUG
#include <stdio.h>
#endif

#include "sha1.h"

#define MIN(a, b) (((a) <= (b)) ? (a) : (b))

static void pad_block(Sha1 *sha1);
static void process_block(Sha1 *sha1);
static inline uint32_t rotl(uint32_t x, int n);
static inline uint32_t f_ch(uint32_t x, uint32_t y, uint32_t z);
static inline uint32_t f_parity(uint32_t x, uint32_t y, uint32_t z);
static inline uint32_t f_maj(uint32_t x, uint32_t y, uint32_t z);
static void put_byte_into_u32be(Sha1 *sha1, uint8_t value);
static uint8_t *write_u32be(uint8_t *p, uint32_t value);

void sha1_init(Sha1 *sha1)
{
#ifdef SHA1_DEBUG
    printf("init()\n");
#endif
    sha1->input_length = 0UL;
    memset(sha1->w, 0, sizeof(sha1->w));
    sha1->pos = 0;
    sha1->h[0] = 0x67452301;
    sha1->h[1] = 0xefcdab89;
    sha1->h[2] = 0x98badcfe;
    sha1->h[3] = 0x10325476;
    sha1->h[4] = 0xc3d2e1f0;
}

void sha1_update(Sha1 *sha1, const uint8_t *data, size_t length)
{
#ifdef SHA1_DEBUG
    printf("update(..., %d)\n", (int) length);
#endif
    const uint8_t *p = data;
    size_t left = length;
    for (;;) {
        size_t copy_length = MIN(left, SHA1_BLOCK_BYTES - sha1->pos);
        for (size_t i = 0; i < copy_length; i++) {
            put_byte_into_u32be(sha1, *p++);
        }
        sha1->input_length += 8UL * copy_length;
        left -= copy_length;
        if (sha1->pos == SHA1_BLOCK_BYTES) {
            process_block(sha1);
        } else {
            break;
        }
    }
}

void sha1_digest(Sha1 *sha1, uint8_t *digest)
{
#ifdef SHA1_DEBUG
    printf("digest()\n");
#endif
    pad_block(sha1);
    uint8_t *p = digest;
    for (size_t i = 0; i < SHA1_DIGEST_WORDS; i++) {
        p = write_u32be(p, sha1->h[i]);
    }
}

static void pad_block(Sha1 *sha1)
{
#ifdef SHA1_DEBUG
    printf("process_block()\n");
#endif
    put_byte_into_u32be(sha1, 0x80);
    if (sha1->pos == SHA1_BLOCK_BYTES) {
        process_block(sha1);
    }
    while (sha1->pos != SHA1_BLOCK_BYTES - 8) {
        put_byte_into_u32be(sha1, 0x00);
        if (sha1->pos == SHA1_BLOCK_BYTES) {
            process_block(sha1);
        }
    }
    sha1->w[SHA1_BLOCK_WORDS - 2] = (uint32_t) (sha1->input_length >> 32);
    sha1->w[SHA1_BLOCK_WORDS - 1] = (uint32_t) sha1->input_length;
    sha1->pos += 8;
    process_block(sha1);
}

static void process_block(Sha1 *sha1)
{

#ifdef SHA1_DEBUG
    printf("process_block()\n");
#endif

    uint32_t a = sha1->h[0];
    uint32_t b = sha1->h[1];
    uint32_t c = sha1->h[2];
    uint32_t d = sha1->h[3];
    uint32_t e = sha1->h[4];

    for (int t = 0; t < 80; t++) {
        uint32_t f;
        uint32_t k;
        if (t < 20) {
            f = f_ch(b, c, d);
            k = 0x5a827999;
        } else if (t < 40) {
            f = f_parity(b, c, d);
            k = 0x6ed9eba1;
        } else if (t < 60) {
            f = f_maj(b, c, d);
            k = 0x8f1bbcdc;
        } else {
            f = f_parity(b, c, d);
            k = 0xca62c1d6;
        }
        if (t >= SHA1_BLOCK_WORDS) {
            sha1->w[t % SHA1_BLOCK_WORDS] = rotl((sha1->w[(t -  3) % SHA1_BLOCK_WORDS] ^
                                                  sha1->w[(t -  8) % SHA1_BLOCK_WORDS] ^
                                                  sha1->w[(t - 14) % SHA1_BLOCK_WORDS] ^
                                                  sha1->w[(t - 16) % SHA1_BLOCK_WORDS]),
                                                 1);
        }

#ifdef SHA1_DEBUG
        printf("w[%2d]=%08x\n", t, sha1->w[t % SHA1_BLOCK_WORDS]);
#endif
        uint32_t temp = rotl(a, 5) + f + e + k + sha1->w[t % SHA1_BLOCK_WORDS];
        e = d;
        d = c;
        c = rotl(b, 30);
        b = a;
        a = temp;
#ifdef SHA1_DEBUG
        printf("t=%2d: %08x %08x %08x %08x %08x\n", t, a, b, c, d, e);
#endif
    }

    sha1->h[0] += a;
    sha1->h[1] += b;
    sha1->h[2] += c;
    sha1->h[3] += d;
    sha1->h[4] += e;
#ifdef SHA1_DEBUG
    printf("\n   h: %08x %08x %08x %08x %08x\n", sha1->h[0], sha1->h[1], sha1->h[2], sha1->h[3], sha1->h[4]);
#endif

    memset(sha1->w, 0, sizeof(sha1->w));
    sha1->pos = 0;
}

static inline uint32_t rotl(uint32_t x, int n)
{
    return (x << n) | (x >> (32 - n));
}

static inline uint32_t f_ch(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) ^ ((~x) & z);
}

static inline uint32_t f_parity(uint32_t x, uint32_t y, uint32_t z)
{
    return x ^ y ^ z;
}

static inline uint32_t f_maj(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) ^ (x & z) ^ (y & z);
}

static void put_byte_into_u32be(Sha1 *sha1, uint8_t value)
{
    uint32_t *word = &sha1->w[sha1->pos / 4];
    size_t shift = (3 - (sha1->pos % 4)) * 8;
    *word = *word | (value << shift);
    sha1->pos++;
}

static uint8_t *write_u32be(uint8_t *p, uint32_t value)
{
    uint32_t x = value;
    for (size_t i = 0; i < 4; i++) {
        *p++ = (x & 0xff000000) >> 24;
        x <<= 8;
    }
    return p;
}
