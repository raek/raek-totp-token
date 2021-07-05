#pragma once

#include "pin.h"
#include "spi.h"

struct Spi {
    Pin *mosi;
    Pin *sck;
    Pin *ss;
};

void spi_bitbang_init(Spi *spi, Pin *mosi, Pin *sck, Pin *ss);
