from typing import Optional


def datetime_is_valid(year: int, month: int, day: int, hour: int, minute: int, second: int) -> bool:
    ...


def datetime_to_unix_time(year: int, month: int, day: int, hour: int, minute: int, second: int) -> Optional[int]:
    ...


class Pin:
    dir_is_output: bool
    output: bool
    input: bool


class Inverter:
    in_pin: Pin
    out_pin: Pin

    def __init__(self, input: Pin, output: Pin) -> None:
        ...

    def run(self) -> None:
        ...


class Sha1:
    def __init__(self) -> None:
        ...

    def update(self, data: bytes) -> None:
        ...

    def digest(self) -> bytes:
        ...
