from string import ascii_lowercase, ascii_uppercase

from firmware import FONT_BLANK_GLYPH, font_lookup, font_render


def test_letters_unique() -> None:
    seen = set()
    for char in ascii_lowercase:
        glyph = font_lookup(char)
        assert glyph not in seen
        seen.add(glyph)


def test_lowercase_and_uppercase_are_same() -> None:
    for lower_char, upper_char in zip(ascii_lowercase, ascii_uppercase):
        lower_glyph = font_lookup(lower_char)
        upper_glyph = font_lookup(upper_char)
        assert lower_glyph == upper_glyph


def test_control_chars_blank() -> None:
    for char in map(chr, range(0x00, 0x20)):
        assert font_lookup(char) == FONT_BLANK_GLYPH


def test_non_asci_chars_blank() -> None:
    for char in map(chr, range(0x80, 0x100)):
        assert font_lookup(char) == FONT_BLANK_GLYPH


def test_render_short() -> None:
    display_width = 8
    text = "hello"
    text_width = len(text)
    glyphs = font_render(display_width, text)
    assert len(glyphs) == display_width
    for glyph, char in zip(glyphs[:text_width], text):
        assert glyph == font_lookup(char)
    for glyph in glyphs[text_width:]:
        assert glyph == FONT_BLANK_GLYPH


def test_render_too_long() -> None:
    display_width = 4
    text = "hello"
    glyphs = font_render(display_width, text)
    assert len(glyphs) == display_width
    for glyph, char in zip(glyphs, text[:display_width]):
        assert glyph == font_lookup(char)
