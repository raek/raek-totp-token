from typing import Any, cast

from hypothesis import given
from hypothesis.strategies import lists, integers
import pytest

from firmware import BitbangSpi, Pin


uint16s = integers(min_value=0, max_value=(2**16-1))


class SpiDevice:
    def __init__(self, received: list[int]) -> None:
        self.mosi = Pin("mosi")
        self.sck = Pin("sck", on_rise=self._shift)
        self.ss = Pin("sck", on_fall=self._begin, on_rise=self._end)
        self.pins = (self.mosi, self.sck, self.ss)
        self.received = received

        self._word = 0

    def is_idle(self) -> bool:
        return not self.sck.output and self.ss.output

    def _begin(self) -> None:
        self._word = 0

    def _shift(self) -> None:
        if not self.ss.output:
            self._word = (self._word << 1) | self.mosi.output

    def _end(self) -> None:
        self.received.append(self._word)


def test_init_and_properties() -> None:
    mosi = Pin("mosi")
    sck = Pin("sck")
    ss = Pin("ss")
    spi = BitbangSpi(mosi, sck, ss)
    assert spi.mosi is mosi
    assert spi.sck is sck
    assert spi.ss is ss


def test_wrong_types() -> None:
    with pytest.raises(TypeError):
        BitbangSpi(cast(Any, 1), cast(Any, 2), cast(Any, 3))


def test_one_transaction() -> None:
    actual: list[int] = []
    expected = 0x1234
    spi_dev = SpiDevice(actual)
    spi = BitbangSpi(*spi_dev.pins)
    actual.clear()
    assert spi_dev.is_idle()
    spi.write(expected)
    assert spi_dev.is_idle()
    assert actual == [expected]


@given(lists(uint16s))
def test_prop_multiple_transactions(words: list[int]) -> None:
    received: list[int] = []
    spi_dev = SpiDevice(received)
    spi = BitbangSpi(*spi_dev.pins)
    received.clear()
    assert spi_dev.is_idle()
    for word in words:
        spi.write(word)
        assert spi_dev.is_idle()
    assert received == words
