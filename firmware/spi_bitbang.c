#include "spi.h"
#include "spi_bitbang.h"

void spi_bitbang_init(Spi *spi, Pin *mosi, Pin *sck, Pin *ss)
{
    spi->mosi = mosi;
    spi->sck = sck;
    spi->ss = ss;
    pin_write(mosi, false);
    pin_set_dir(mosi, PIN_DIR_OUTPUT);
    pin_write(sck, false);
    pin_set_dir(sck, PIN_DIR_OUTPUT);
    pin_write(ss, true);
    pin_set_dir(ss, PIN_DIR_OUTPUT);
}

void spi_write(Spi *spi, uint16_t data)
{
    uint16_t x = data;
    pin_write(spi->ss, false);
    for (int i = 0; i < 16; i++) {
        bool bit = (x & 0x8000) != 0;
        pin_write(spi->mosi, bit);
        x <<= 1;
        pin_write(spi->sck, true);
        pin_write(spi->sck, false);
    }
    pin_write(spi->ss, true);
}
