from hashlib import sha1 as sha1_oracle

from hypothesis import given
from hypothesis.strategies import binary, lists

from firmware import Sha1


def test_empty() -> None:
    assert Sha1().digest().hex() == sha1_oracle().digest().hex()


def test_short() -> None:
    chunk = b"abc"
    actual = Sha1()
    expected = sha1_oracle()
    actual.update(chunk)
    expected.update(chunk)
    assert actual.digest().hex() == expected.digest().hex()


def test_padding_up_to_one_fits_in_first_block() -> None:
    actual = Sha1()
    expected = sha1_oracle()
    chunk = b"x" * (expected.block_size - 1)
    actual.update(chunk)
    expected.update(chunk)
    assert actual.digest().hex() == expected.digest().hex()


def test_padding_up_to_zeroes_fits_in_first_block() -> None:
    actual = Sha1()
    expected = sha1_oracle()
    chunk = b"x" * (expected.block_size - 2)
    actual.update(chunk)
    expected.update(chunk)
    assert actual.digest().hex() == expected.digest().hex()


def test_padding_up_to_length_fits_in_same_block() -> None:
    actual = Sha1()
    expected = sha1_oracle()
    chunk = b"x" * (expected.block_size - 9)
    actual.update(chunk)
    expected.update(chunk)
    assert actual.digest().hex() == expected.digest().hex()


@given(lists(binary()))
def test_comparing_to_python_version(chunks: list[bytes]) -> None:
    actual = Sha1()
    expected = sha1_oracle()
    for chunk in chunks:
        actual.update(chunk)
        expected.update(chunk)
    assert actual.digest().hex() == expected.digest().hex()
