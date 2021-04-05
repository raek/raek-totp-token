from datetime import datetime, timezone

from hypothesis import given
from hypothesis.strategies import integers

from firmware import datetime_is_valid, datetime_to_unix_time


valid_unix_times = integers(min_value=0, max_value=(2**32-1))


def test_epoch():
    assert datetime_is_valid(1970, 1, 1, 0, 0, 0)
    assert datetime_to_unix_time(1970, 1, 1, 0, 0, 0) == 0


def test_some_valid():
    assert datetime_is_valid(2009, 2, 13, 23, 31, 30)
    assert datetime_to_unix_time(2009, 2, 13, 23, 31, 30) == 1234567890


def test_last_valid():
    assert datetime_is_valid(2106, 2, 7, 6, 28, 15)
    assert datetime_to_unix_time(2106, 2, 7, 6, 28, 15) == 2**32 - 1


@given(valid_unix_times)
def test_any_valid(unix_time):
    dt = datetime.fromtimestamp(unix_time, tz=timezone.utc)
    assert datetime_is_valid(*dt.timetuple()[0:6])
    assert datetime_to_unix_time(*dt.timetuple()[0:6]) == unix_time


def test_valid_days_in_february():
    assert datetime_is_valid(2000, 2, 29, 0, 0, 0)
    assert datetime_is_valid(2001, 2, 28, 0, 0, 0)
    assert datetime_is_valid(2004, 2, 29, 0, 0, 0)
    assert datetime_is_valid(2100, 2, 28, 0, 0, 0)
    assert datetime_to_unix_time(2000, 2, 29, 0, 0, 0) is not None
    assert datetime_to_unix_time(2001, 2, 28, 0, 0, 0) is not None
    assert datetime_to_unix_time(2004, 2, 29, 0, 0, 0) is not None
    assert datetime_to_unix_time(2100, 2, 28, 0, 0, 0) is not None


def test_invalid_month():
    assert not datetime_is_valid(2000, 0, 1, 0, 0, 0)
    assert not datetime_is_valid(2000, 13, 1, 0, 0, 0)
    assert datetime_to_unix_time(2000, 0, 1, 0, 0, 0) is None
    assert datetime_to_unix_time(2000, 13, 1, 0, 0, 0) is None


def test_invalid_day():
    assert not datetime_is_valid(2000, 1, 0, 0, 0, 0)
    assert not datetime_is_valid(2000, 1, 32, 0, 0, 0)
    assert not datetime_is_valid(2000, 3, 32, 0, 0, 0)
    assert not datetime_is_valid(2000, 4, 31, 0, 0, 0)
    assert not datetime_is_valid(2000, 5, 32, 0, 0, 0)
    assert not datetime_is_valid(2000, 6, 31, 0, 0, 0)
    assert not datetime_is_valid(2000, 7, 32, 0, 0, 0)
    assert not datetime_is_valid(2000, 8, 32, 0, 0, 0)
    assert not datetime_is_valid(2000, 9, 31, 0, 0, 0)
    assert not datetime_is_valid(2000, 10, 32, 0, 0, 0)
    assert not datetime_is_valid(2000, 11, 31, 0, 0, 0)
    assert not datetime_is_valid(2000, 12, 32, 0, 0, 0)
    assert datetime_to_unix_time(2000, 1, 0, 0, 0, 0) is None
    assert datetime_to_unix_time(2000, 1, 32, 0, 0, 0) is None
    assert datetime_to_unix_time(2000, 3, 32, 0, 0, 0) is None
    assert datetime_to_unix_time(2000, 4, 31, 0, 0, 0) is None
    assert datetime_to_unix_time(2000, 5, 32, 0, 0, 0) is None
    assert datetime_to_unix_time(2000, 6, 31, 0, 0, 0) is None
    assert datetime_to_unix_time(2000, 7, 32, 0, 0, 0) is None
    assert datetime_to_unix_time(2000, 8, 32, 0, 0, 0) is None
    assert datetime_to_unix_time(2000, 9, 31, 0, 0, 0) is None
    assert datetime_to_unix_time(2000, 10, 32, 0, 0, 0) is None
    assert datetime_to_unix_time(2000, 11, 31, 0, 0, 0) is None
    assert datetime_to_unix_time(2000, 12, 32, 0, 0, 0) is None


def test_invalid_days_in_february():
    assert not datetime_is_valid(2000, 2, 30, 0, 0, 0)
    assert not datetime_is_valid(2001, 2, 29, 0, 0, 0)
    assert not datetime_is_valid(2004, 2, 30, 0, 0, 0)
    assert not datetime_is_valid(2100, 2, 29, 0, 0, 0)
    assert datetime_to_unix_time(2000, 2, 30, 0, 0, 0) is None
    assert datetime_to_unix_time(2001, 2, 29, 0, 0, 0) is None
    assert datetime_to_unix_time(2004, 2, 30, 0, 0, 0) is None
    assert datetime_to_unix_time(2100, 2, 29, 0, 0, 0) is None


def test_invalid_hour():
    assert not datetime_is_valid(2000, 1, 1, 24, 0, 0)
    assert datetime_to_unix_time(2000, 1, 1, 24, 0, 0) is None


def test_invalid_minute():
    assert not datetime_is_valid(2000, 1, 1, 0, 60, 0)
    assert datetime_to_unix_time(2000, 1, 1, 0, 60, 0) is None


def test_invalid_second():
    assert not datetime_is_valid(2000, 1, 1, 0, 0, 60)
    assert datetime_to_unix_time(2000, 1, 1, 0, 0, 60) is None


def test_invalid_before_first_valid():
    unix_time = -1
    dt = datetime.fromtimestamp(unix_time, tz=timezone.utc)
    assert not datetime_is_valid(*dt.timetuple()[0:6])
    assert datetime_to_unix_time(*dt.timetuple()[0:6]) is None


def test_invalid_after_last_valid():
    unix_time = 2**32
    dt = datetime.fromtimestamp(unix_time, tz=timezone.utc)
    assert not datetime_is_valid(*dt.timetuple()[0:6])
    assert datetime_to_unix_time(*dt.timetuple()[0:6]) is None


last_year_beginning = datetime(2106, 1, 1, 0, 0, 0, tzinfo=timezone.utc).timestamp()
last_year_end = datetime(2106, 12, 31, 23, 59, 59, tzinfo=timezone.utc).timestamp()


@given(integers(min_value=last_year_beginning, max_value=last_year_end))
def test_last_year(unix_time):
    dt = datetime.fromtimestamp(unix_time, tz=timezone.utc)
    valid = datetime_is_valid(*dt.timetuple()[0:6])
    value = datetime_to_unix_time(*dt.timetuple()[0:6])
    if unix_time < 2**32:
        assert valid
        assert value == unix_time
    else:
        assert not valid
        assert value is None


@given(integers(min_value=1970, max_value=2105),
       integers(min_value=1, max_value=12),
       integers(min_value=28, max_value=31))
def test_any_end_of_month(year, month, day):
    valid = datetime_is_valid(year, month, day, 0, 0, 0)
    value = datetime_to_unix_time(year, month, day, 0, 0, 0)
    try:
        dt = datetime(year, month, day, 0, 0, 0, tzinfo=timezone.utc)
        unix_time = dt.timestamp()
        assert valid
        assert value == unix_time
    except ValueError:
        assert not valid
        assert value is None
