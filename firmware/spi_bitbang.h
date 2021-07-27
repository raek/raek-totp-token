#pragma once

#include "spi.h"
#include "pin.h"

struct spi {
    struct pin *mosi;
    struct pin *sck;
    struct pin *ss;
};

void spi_bitbang_init(struct spi *spi, struct pin *mosi, struct pin *sck, struct pin *ss);
