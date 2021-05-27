#include "sha1.h"

void sha1_init(Sha1 *sha1)
{
    sha1->dummy = 0;
}

void sha1_update(Sha1 *sha1, const uint8_t *data, size_t length)
{
}

void sha1_digest(Sha1 *sha1, uint8_t *digest)
{
    for (size_t i = 0; i < SHA1_DIGEST_BYTES; i++) {
        digest[i] = 0;
    }
}
