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
static uint8_t *read_u32be(uint8_t *p, uint32_t *value);
static uint8_t *write_u32be(uint8_t *p, uint32_t value);
static uint8_t *write_u64be(uint8_t *p, uint64_t value);

void sha1_init(Sha1 *sha1)
{
#ifdef SHA1_DEBUG
    printf("init()\n");
#endif
    sha1->total_length = 0UL;
    memset(sha1->block, 0, SHA1_BLOCK_BYTES);
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
        sha1->total_length += 8UL * (uint64_t) copy_length;
        memcpy(&sha1->block[sha1->pos], p, copy_length);
        p += copy_length;
        left -= copy_length;
        sha1->pos += copy_length;
        if (sha1->pos == SHA1_BLOCK_BYTES) {
            process_block(sha1);
            sha1->pos = 0;
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
    for (int i = 0; i < SHA1_DIGEST_WORDS; i++) {
        p = write_u32be(p, sha1->h[i]);
    }
}

static void pad_block(Sha1 *sha1)
{
#ifdef SHA1_DEBUG
    printf("process_block()\n");
#endif
    sha1->block[sha1->pos++] = 0x80;
    if (sha1->pos == SHA1_BLOCK_BYTES) {
        process_block(sha1);
        sha1->pos = 0;
    }
    while (sha1->pos != SHA1_BLOCK_BYTES - 8) {
        sha1->block[sha1->pos++] = 0x00;
        if (sha1->pos == SHA1_BLOCK_BYTES) {
            process_block(sha1);
            sha1->pos = 0;
        }
    }
    write_u64be(&sha1->block[sha1->pos], sha1->total_length);
    sha1->pos += 8;
    process_block(sha1);
    sha1->pos = 0;
}

static void process_block(Sha1 *sha1)
{
#ifdef SHA1_DEBUG
    printf("process_block()\n");
    printf(" blk: ");
    for (int i = 0; i < SHA1_BLOCK_BYTES; i++) {
        printf("%02x%s", sha1->block[i], ((i+1) % 4 == 0 ? " " : ""));
    }
    printf("\n");
#endif

    uint8_t *p = sha1->block;
    for (int i = 0; i < 16; i++) {
        p = read_u32be(p, &sha1->w[i]);
    }
    for (int i = 16; i < 80; i++) {
        sha1->w[i] = rotl(sha1->w[i-3] ^ sha1->w[i-8] ^ sha1->w[i-14] ^ sha1->w[i-16], 1);
    }
#ifdef SHA1_DEBUG
    printf("   w: ");
    for (int i = 0; i < 80; i++) {
        printf("%08x ", sha1->w[i]);
    }
    printf("\n");
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
        uint32_t temp = rotl(a, 5) + f + e + k + sha1->w[t];
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
    printf("   h: %08x %08x %08x %08x %08x\n", sha1->h[0], sha1->h[1], sha1->h[2], sha1->h[3], sha1->h[4]);
#endif
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

static uint8_t *read_u32be(uint8_t *p, uint32_t *value)
{
    uint32_t result = 0;
    for (int i = 0; i < 4; i++) {
        result <<= 8;
        result |= *p++;
    }
    *value = result;
    return p;
}

static uint8_t *write_u32be(uint8_t *p, uint32_t value)
{
    uint32_t x = value;
    for (int i = 0; i < 4; i++) {
        *p++ = (x & 0xff000000) >> 24;
        x <<= 8;
    }
    return p;
}

static uint8_t *write_u64be(uint8_t *p, uint64_t value)
{
    uint64_t x = value;
    for (int i = 0; i < 8; i++) {
        *p++ = (x & 0xff00000000000000UL) >> 56;
        x <<= 8;
    }
    return p;
}
