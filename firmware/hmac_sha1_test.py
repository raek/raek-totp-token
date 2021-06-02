from hmac import digest as hmac_oracle

from hypothesis import given
from hypothesis.strategies import binary

from firmware import hmac_sha1


def test_example() -> None:
    key = b"key"
    message = b"The quick brown fox jumps over the lazy dog"
    code = bytes.fromhex("de7c9b85b8b78aa6bc8a7a36f70a90701c9db4d9")
    assert hmac_sha1(key, message) == code


@given(binary(), binary())
def test_comparing_to_python_version(key: bytes, message: bytes) -> None:
    actual = hmac_sha1(key, message)
    expected = hmac_oracle(key, message, "sha1")
    assert actual == expected
