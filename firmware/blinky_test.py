import pytest
from typing import Any, cast

from firmware import Pin, Pinint, Blinky


def test_init_and_properties() -> None:
    button_pinint = Pinint("button")
    button_pin = Pin("button")
    led_pin = Pin("led")
    blinky = Blinky(button_pinint, button_pin, led_pin)
    assert blinky.button_pin is button_pin
    assert blinky.led_pin is led_pin


def test_init_wrong_types() -> None:
    with pytest.raises(TypeError):
        Blinky(cast(Any, 1), cast(Any, 2), cast(Any, 3))


def test_run() -> None:
    button_pinint = Pinint("button")
    button_pin = Pin("button")
    button_pin.input = False
    led_pin = Pin("led")
    blinky = Blinky(button_pinint, button_pin, led_pin)
    assert button_pin.dir_is_output is False
    assert led_pin.dir_is_output is True
    assert led_pin.output is True

    button_pinint.trigger_rise()
    assert led_pin.output is False
    button_pinint.trigger_fall()
    assert led_pin.output is True

    del blinky


def test_access_attriutes() -> None:
    button_pinint = Pinint("button")
    button_pin = Pin("button")
    led_pin = Pin("led")
    blinky = Blinky(button_pinint, button_pin, led_pin)
    assert blinky.button_pinint is button_pinint
    assert blinky.button_pin is button_pin
    assert blinky.led_pin is led_pin
