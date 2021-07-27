#pragma once

// Limited SPI interface
//
// * Master only
// * Single slave
// * Write only
// * 16-bit MSB-first transactions only
// * CPOL=0, CPHA=0 only

#include <stdint.h>

struct spi;

void spi_write(struct spi *spi, uint16_t data);
