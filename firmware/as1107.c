#include "as1107.h"
#include "spi.h"

#define REG_NO_OP          0x00
#define REG_DIGIT_0        0x01
#define REG_DECODE_ENABLE  0x09
#define REG_INTENSITY      0x0a
#define REG_SCAN_LIMIT     0x0b
#define REG_SHUTDOWN       0x0c
#define REG_FEATURE        0x0e
#define REG_DISPLAY_TEST   0x0f

#define SHUTDOWN_NORMAL       (1<<0)
#define SHUTDOWN_KEEP_FEATURE (1<<7)

#define FEAT_CLK_EN         (1<<0)
#define FEAT_REG_RES        (1<<1)
#define FEAT_DECODE_SEL     (1<<2)
#define FEAT_SPI_EN         (1<<3)
#define FEAT_BLINK_EN       (1<<4)
#define FEAT_BLINK_FREQ_SEL (1<<5)
#define FEAT_SYNC           (1<<6)
#define FEAT_BLINK_START    (1<<7)

static void set_reg(struct as1107 *as1107, uint8_t reg, uint8_t value)
{
    uint16_t data = (((uint16_t) reg) << 8) | ((uint16_t) value);
    spi_write(as1107->spi, data);
}

void as1107_init(struct as1107 *as1107, struct spi *spi)
{
    as1107->spi = spi;
    set_reg(as1107, REG_SHUTDOWN, 0);
    for (int i = 0; i < AS1107_GLYPH_COUNT; i++) {
        set_reg(as1107, (uint8_t) (REG_DIGIT_0 + i), 0);
    }
    set_reg(as1107, REG_FEATURE, FEAT_REG_RES);
    set_reg(as1107, REG_FEATURE, 0);
    set_reg(as1107, REG_DECODE_ENABLE, 0);
    set_reg(as1107, REG_INTENSITY, AS1107_INTENSITY_MAX);
    set_reg(as1107, REG_SCAN_LIMIT, 7);
    set_reg(as1107, REG_SHUTDOWN, SHUTDOWN_KEEP_FEATURE | SHUTDOWN_NORMAL);
}

void as1107_set_test_mode(struct as1107 *as1107, bool test_mode_on)
{
    set_reg(as1107, REG_DISPLAY_TEST, test_mode_on ? 0x01 : 0x00);
}

void as1107_set_intensity(struct as1107 *as1107, uint8_t intensity)
{
    set_reg(as1107, REG_INTENSITY, intensity);
}

void as1107_show_glyphs(struct as1107 *as1107, const uint8_t *glyphs)
{
    for (int i = 0; i < AS1107_GLYPH_COUNT; i++) {
        set_reg(as1107, (uint8_t) (REG_DIGIT_0 + i), glyphs[i]);
    }
    as1107_resume(as1107);
}

void as1107_blank(struct as1107 *as1107)
{
    set_reg(as1107, REG_SHUTDOWN, SHUTDOWN_KEEP_FEATURE);
}

void as1107_resume(struct as1107 *as1107)
{
    set_reg(as1107, REG_SHUTDOWN, SHUTDOWN_KEEP_FEATURE | SHUTDOWN_NORMAL);
}
