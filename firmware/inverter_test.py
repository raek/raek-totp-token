import pytest
from typing import Any, cast

from firmware import Pin, Pinint, Inverter


def test_init_and_properties() -> None:
    in_pinint = Pinint("in")
    in_pin = Pin("in")
    out_pin = Pin("out")
    inverter = Inverter(in_pinint, in_pin, out_pin)
    assert inverter.in_pin is in_pin
    assert inverter.out_pin is out_pin


def test_init_wrong_types() -> None:
    with pytest.raises(TypeError):
        Inverter(cast(Any, 1), cast(Any, 2), cast(Any, 3))


def test_run() -> None:
    in_pinint = Pinint("in")
    in_pin = Pin("in")
    in_pin.input = False
    out_pin = Pin("out")
    inverter = Inverter(in_pinint, in_pin, out_pin)
    assert in_pin.dir_is_output is False
    assert out_pin.dir_is_output is True
    assert out_pin.output is True

    in_pinint.trigger_rise()
    assert out_pin.output is False
    in_pinint.trigger_fall()
    assert out_pin.output is True

    del inverter


def test_access_attriutes() -> None:
    in_pinint = Pinint("in")
    in_pin = Pin("in")
    out_pin = Pin("out")
    inverter = Inverter(in_pinint, in_pin, out_pin)
    assert inverter.in_pinint is in_pinint
    assert inverter.in_pin is in_pin
    assert inverter.out_pin is out_pin
