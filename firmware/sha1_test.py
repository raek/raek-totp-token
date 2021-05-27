from hashlib import sha1 as sha1_oracle

from hypothesis import given
from hypothesis.strategies import binary, lists

from firmware import Sha1


@given(lists(binary()))
def test_sha1(chunks: list[bytes]) -> None:
    expected = sha1_oracle()
    actual = Sha1()
    for chunk in chunks:
        expected.update(chunk)
        actual.update(chunk)
    assert expected.digest() == actual.digest()
