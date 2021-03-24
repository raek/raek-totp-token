from firmware import datetime_to_unix_time

def test_datetime_epoch():
    assert datetime_to_unix_time(1970, 1, 1, 0, 0, 0) == 0
