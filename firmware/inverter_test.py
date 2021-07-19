import pytest
from typing import Any, cast

from firmware import Pin, Inverter


def test_init_and_properties() -> None:
    in_pin = Pin("in")
    out_pin = Pin("out")
    inverter = Inverter(in_pin, out_pin)
    assert inverter.in_pin is in_pin
    assert inverter.out_pin is out_pin


def test_init_wrong_types() -> None:
    with pytest.raises(TypeError):
        Inverter(cast(Any, 1), cast(Any, 2))


def test_run() -> None:
    in_pin = Pin("in")
    out_pin = Pin("out")
    inverter = Inverter(in_pin, out_pin)
    print(in_pin)
    assert in_pin.dir_is_output is False
    print(out_pin)
    assert out_pin.dir_is_output is True

    in_pin.input = False
    inverter.run()
    assert out_pin.output is True

    in_pin.input = True
    inverter.run()
    assert out_pin.output is False


def test_access_attriutes() -> None:
    in_pin = Pin("in")
    out_pin = Pin("out")
    inverter = Inverter(in_pin, out_pin)
    assert inverter.in_pin is in_pin
    assert inverter.out_pin is out_pin
