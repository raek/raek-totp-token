from firmware import format_decimal


def test_space_padded_nonzero() -> None:
    assert format_decimal(8, 123, " ") == "     123"


def test_zero_padded_nonzero() -> None:
    assert format_decimal(8, 123, "0") == "00000123"


def test_space_padded_zero() -> None:
    assert format_decimal(8, 0, " ") == "       0"


def test_zero_padded_zero() -> None:
    assert format_decimal(8, 0, "0") == "00000000"


def test_trucated() -> None:
    assert format_decimal(3, 123456, " ") == "456"
