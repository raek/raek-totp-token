from firmware import datetime_to_unix_time

def test_epoch():
    assert datetime_to_unix_time(1970, 1, 1, 0, 0, 0) == 0

def test_arbitrary_valid():
    assert datetime_to_unix_time(2009, 2, 13, 23, 31, 30) == 1234567890
