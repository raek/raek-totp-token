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


def test_valid_days_in_february():
    assert datetime_to_unix_time(2000, 2, 29, 0, 0, 0) != None
    assert datetime_to_unix_time(2001, 2, 28, 0, 0, 0) != None
    assert datetime_to_unix_time(2004, 2, 29, 0, 0, 0) != None
    assert datetime_to_unix_time(2100, 2, 28, 0, 0, 0) != None


def test_invalid_month():
    assert datetime_to_unix_time(2000, 0, 1, 0, 0, 0) == None
    assert datetime_to_unix_time(2000, 13, 1, 0, 0, 0) == None


def test_invalid_day():
    assert datetime_to_unix_time(2000, 1, 0, 0, 0, 0) == None
    assert datetime_to_unix_time(2000, 1, 32, 0, 0, 0) == None
    assert datetime_to_unix_time(2000, 3, 32, 0, 0, 0) == None
    assert datetime_to_unix_time(2000, 4, 31, 0, 0, 0) == None
    assert datetime_to_unix_time(2000, 5, 32, 0, 0, 0) == None
    assert datetime_to_unix_time(2000, 6, 31, 0, 0, 0) == None
    assert datetime_to_unix_time(2000, 7, 32, 0, 0, 0) == None
    assert datetime_to_unix_time(2000, 8, 32, 0, 0, 0) == None
    assert datetime_to_unix_time(2000, 9, 31, 0, 0, 0) == None
    assert datetime_to_unix_time(2000, 10, 32, 0, 0, 0) == None
    assert datetime_to_unix_time(2000, 11, 31, 0, 0, 0) == None
    assert datetime_to_unix_time(2000, 12, 32, 0, 0, 0) == None


def test_invalid_days_in_february():
    assert datetime_to_unix_time(2000, 2, 30, 0, 0, 0) == None
    assert datetime_to_unix_time(2001, 2, 29, 0, 0, 0) == None
    assert datetime_to_unix_time(2004, 2, 30, 0, 0, 0) == None
    assert datetime_to_unix_time(2100, 2, 29, 0, 0, 0) == None


def test_invalid_hour():
    assert datetime_to_unix_time(2000, 1, 1, 24, 0, 0) == None


def test_invalid_minute():
    assert datetime_to_unix_time(2000, 1, 1, 0, 60, 0) == None


def test_invalid_second():
    assert datetime_to_unix_time(2000, 1, 1, 0, 0, 60) == None
