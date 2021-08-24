#include <avr/io.h>

#include "i2c.h"
#include "i2c_avr.h"

#define I2C_FREQUENCY_HZ 400000UL
#define I2C_WRITE 0x00
#define I2C_READ 0x01

static inline void i2c_step(uint8_t flags);
static inline uint8_t i2c_wait(void);

void i2c_system_init(void)
{
    DDRD &= ~((1<<1) | (1<<0));
    PORTD |= (1<<1) | (1<<0);
    TWBR = ((F_CPU / I2C_FREQUENCY_HZ) - 16UL) / 2UL;
    TWCR = ((0<<TWINT) |
            (0<<TWEA) |
            (0<<TWSTA) |
            (0<<TWSTO) |
            (0<<TWWC) |
            (1<<TWEN) |
            (0<<TWIE));
    TWSR = ((0<<TWPS1) |
            (0<<TWPS0));
}

enum result i2c_read(uint8_t addr, uint8_t *data, size_t length)
{
    i2c_step(1<<TWSTA);
    if (i2c_wait() != 0x08) {
        return ERROR("i2c_read start");
    }
    TWDR = (addr<<1) | I2C_READ;
    i2c_step(0);
    if (i2c_wait() != 0x40) {
        i2c_step(1<<TWSTO);
        return ERROR("i2c_read addr ack");
    }
    if (length == 0) {
        i2c_step(1<<TWSTO);
        return RESULT_OK;
    }
    for (size_t i = 0; i < (length-1); i++) {
        i2c_step(1<<TWEA);
        if (i2c_wait() != 0x50) {
            i2c_step(1<<TWSTO);
            return ERROR("i2c_read data ack");
        }
        data[i] = TWDR;
    }
    i2c_step(0);
    if (i2c_wait() != 0x58) {
        i2c_step(1<<TWSTO);
        return ERROR("i2c_read last data ack");
    }
    data[length-1] = TWDR;
    i2c_step(1<<TWSTO);
    return RESULT_OK;
}

enum result i2c_write(uint8_t addr, uint8_t *data, size_t length)
{
    i2c_step(1<<TWSTA);
    if (i2c_wait() != 0x08) {
        return ERROR("i2c_write start");
    }
    TWDR = (addr<<1) | I2C_WRITE;
    i2c_step(0);
    if (i2c_wait() != 0x18) {
        i2c_step(1<<TWSTO);
        return ERROR("i2c_write addr ack");
    }
    for (size_t i = 0; i < length; i++) {
        TWDR = data[i];
        i2c_step(0);
        if (i2c_wait() != 0x28) {
            i2c_step(1<<TWSTO);
            return ERROR("i2c_write data ack");
        }
    }
    i2c_step(1<<TWSTO);
    return RESULT_OK;
}

static inline void i2c_step(uint8_t flags) {
    TWCR = (1<<TWINT) | (1<<TWEN) | flags;
}

static inline uint8_t i2c_wait(void)
{
    while (!(TWCR & (1<<TWINT))) {
    }
    return TWSR & 0xF8;
}
