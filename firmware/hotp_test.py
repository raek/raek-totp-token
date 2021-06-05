from base64 import b32encode

from hypothesis import given
from hypothesis.strategies import binary, integers
import pyotp

from firmware import hotp


def hotp_oracle(secret: bytes, counter: int) -> str:
    b32_secret = b32encode(secret).decode("ascii")
    return pyotp.HOTP(b32_secret).at(counter)


secrets = binary(min_size=20)
counters = integers(min_value=0, max_value=(2**64-1))


def test_example() -> None:
    secret = b"12345678901234567890"
    expected_otps = [
        "755224",
        "287082",
        "359152",
        "969429",
        "338314",
        "254676",
        "287922",
        "162583",
        "399871",
        "520489",
    ]
    actual_otps = [hotp(secret, i) for i in range(len(expected_otps))]
    assert actual_otps == expected_otps


@given(secrets, counters)
def test_any(secret: bytes, counter: int) -> None:
    assert hotp(secret, counter) == hotp_oracle(secret, counter)


@given(secrets)
def test_ten_first(secret: bytes) -> None:
    actual = [hotp(secret, counter) for counter in range(10)]
    expected = [hotp_oracle(secret, counter) for counter in range(10)]
    assert actual == expected
