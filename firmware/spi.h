#pragma once

// Limited SPI interface
//
// * Master only
// * Single slave
// * Write only
// * 16-bit MSB-first transactions only
// * CPOL=0, CPHA=0 only

#include <stdint.h>

struct Spi;
typedef struct Spi Spi;

void spi_write(Spi *spi, uint16_t data);
