from datetime import datetime, timezone

from hypothesis import given
from hypothesis.strategies import integers

from firmware import datetime_to_unix_time


valid_unix_times = integers(min_value=0, max_value=(2**32-1))


def test_epoch():
    assert datetime_to_unix_time(1970, 1, 1, 0, 0, 0) == 0


def test_some_valid():
    assert datetime_to_unix_time(2009, 2, 13, 23, 31, 30) == 1234567890


def test_last_valid():
    assert datetime_to_unix_time(2106, 2, 7, 6, 28, 15) == 2**32 - 1


@given(valid_unix_times)
def test_any_valid(unix_time):
    dt = datetime.fromtimestamp(unix_time, tz=timezone.utc)
    assert datetime_to_unix_time(*dt.timetuple()[0:6]) == unix_time
