from typing import Callable, NamedTuple, Optional, cast
from weakref import WeakValueDictionary

import cffi  # type: ignore

import pure_cffi  # type: ignore
import blinky_cffi  # type: ignore
import spi_bitbang_cffi  # type: ignore


ffi = cffi.FFI()


datetime_is_valid = pure_cffi.lib.datetime_is_valid


def datetime_to_unix_time(year: int, month: int, day: int, hour: int, minute: int, second: int) -> Optional[int]:
    result = pure_cffi.ffi.new("unix_time *", 0)
    if pure_cffi.lib.datetime_to_unix_time(result, year, month, day, hour, minute, second):
        return cast(int, result[0])
    else:
        return None


class Sha1:
    def __init__(self) -> None:
        self._cdata = pure_cffi.ffi.new("struct sha1 *")
        pure_cffi.lib.sha1_init(self._cdata)

    def update(self, chunk: bytes) -> None:
        pure_cffi.lib.sha1_update(self._cdata, chunk, len(chunk))

    def digest(self) -> bytes:
        digest = pure_cffi.ffi.new("uint8_t[]", pure_cffi.lib.SHA1_DIGEST_BYTES)
        pure_cffi.lib.sha1_digest(self._cdata, digest)
        return bytes(digest)


def hmac_sha1(key: bytes, message: bytes) -> bytes:
    scratchpad = pure_cffi.ffi.new("struct hmac_sha1 *")
    code = pure_cffi.ffi.new("uint8_t[]", pure_cffi.lib.HMAC_SHA1_CODE_BYTES)
    pure_cffi.lib.hmac_sha1(scratchpad, key, len(key), message, len(message), code)
    return bytes(code)


def hotp(secret: bytes, counter: int) -> str:
    scratchpad = pure_cffi.ffi.new("struct hotp *")
    output = pure_cffi.ffi.new("char[]", pure_cffi.lib.HOTP_DIGITS)
    pure_cffi.lib.hotp(scratchpad, secret, len(secret), counter, output)
    return cast(bytes, pure_cffi.ffi.string(output)).decode("ascii")


FONT_BLANK_GLYPH: int = pure_cffi.lib.FONT_BLANK_GLYPH


def font_lookup(char: str) -> int:
    return cast(int, pure_cffi.lib.font_lookup(char.encode("latin1")))


def font_render(width: int, string: str) -> bytes:
    buffer = pure_cffi.ffi.new("uint8_t[]", width)
    pure_cffi.lib.font_render(buffer, width, string.encode("latin1"))
    return bytes(buffer)


Sig = int


class Actor:
    def __init__(self, cdata: cffi.FFI.CData) -> None:
        self._cdata = cdata
        self._children: list[cffi.FFI.CData] = []

    def add_child(self, child: cffi.FFI.CData) -> None:
        self._children.append(child)

    def post(self, sig: Sig) -> None:
        self._cdata.dispatcher(self.cdata, sig)

    @property
    def cdata(self) -> cffi.FFI.CData:
        return self._cdata


ACTORS: WeakValueDictionary[cffi.FFI.CData, Actor] = WeakValueDictionary()
LAST_ACTOR: Optional[Actor] = None


def get_last_actor() -> Actor:
    global LAST_ACTOR
    assert LAST_ACTOR is not None
    actor = LAST_ACTOR
    LAST_ACTOR = None
    return actor


Dispatcher = Callable[[cffi.FFI.CData, Sig], None]


@blinky_cffi.ffi.def_extern()
def actor_init(actor_ptr: cffi.FFI.CData, dispatcher: Dispatcher) -> None:
    global LAST_ACTOR
    assert actor_ptr not in ACTORS
    actor_ptr.dispatcher = dispatcher
    actor = Actor(actor_ptr)
    ACTORS[actor_ptr] = actor
    LAST_ACTOR = actor


@blinky_cffi.ffi.def_extern()
def actor_post(actor_ptr: cffi.FFI.CData, sig: Sig) -> None:
    ACTORS[actor_ptr].post(sig)


Instant = int  # milliseconds
Duration = int  # milliseconds


CURRENT_TIME: Instant = 0


class Timer:
    def __init__(self, cdata: cffi.FFI.CData, recipient: Actor, sig: Sig) -> None:
        self._cdata = cdata
        self._cdata.recipient = recipient.cdata
        self._cdata.sig = sig
        self._cdata.active = False

    def set_oneshot(self, delay: Duration) -> None:
        self._cdata.active = False
        self._cdata.target = CURRENT_TIME + delay
        self._cdata.repeating = False
        self._cdata.active = True

    def set_repeating(self, interval: Duration) -> None:
        self._cdata.active = False
        self._cdata.target = CURRENT_TIME + interval
        self._cdata.repeating = True
        self._cdata.interval = interval
        self._cdata.fixed_count = False
        self._cdata.active = True

    def set_fixed_count(self, interval: Duration, count: int) -> None:
        self._cdata.active = False
        if count <= 0:
            return
        self._cdata.target = CURRENT_TIME + interval
        self._cdata.repeating = True
        self._cdata.interval = interval
        self._cdata.fixed_count = True
        self._cdata.count = count
        self._cdata.active = True

    def cancel(self) -> None:
        self._cdata.active = False

    def service(self) -> None:
        if not self._cdata.active:
            return
        if self._cdata.target != CURRENT_TIME:
            return
        ACTORS[self._cdata.recipient].post(self._cdata.sig)
        if self._cdata.repeating:
            self._cdata.target += self._cdata.interval
            if self._cdata.fixed_count:
                self._cdata.count -= 1
                if self._cdata.count == 0:
                    self._cdata.active = False

    @property
    def cdata(self) -> cffi.FFI.CData:
        return self._cdata


TIMERS: WeakValueDictionary[cffi.FFI.CData, Timer] = WeakValueDictionary()


def step_time_forward(duration: Duration) -> None:
    global CURRENT_TIME
    for _ in range(duration):
        CURRENT_TIME += 1
        for timer in TIMERS.values():
            timer.service()


@blinky_cffi.ffi.def_extern()
def timer_init(timer_ptr: cffi.FFI.CData, recipient_ptr: cffi.FFI.CData, sig: Sig) -> None:
    assert timer_ptr not in TIMERS
    recipient = ACTORS[recipient_ptr]
    timer = Timer(timer_ptr, recipient, sig)
    recipient.add_child(timer)
    TIMERS[timer_ptr] = timer


@blinky_cffi.ffi.def_extern()
def timer_set_oneshot(timer_ptr: cffi.FFI.CData, delay: Duration) -> None:
    TIMERS[timer_ptr].set_oneshot(delay)


@blinky_cffi.ffi.def_extern()
def timer_set_repeating(timer_ptr: cffi.FFI.CData, interval: Duration) -> None:
    TIMERS[timer_ptr].set_repeating(interval)


@blinky_cffi.ffi.def_extern()
def timer_set_fixed_count(timer_ptr: cffi.FFI.CData, interval: Duration, count: int) -> None:
    TIMERS[timer_ptr].set_fixed_count(interval, count)


@blinky_cffi.ffi.def_extern()
def timer_cancel(timer_ptr: cffi.FFI.CData) -> None:
    TIMERS[timer_ptr].cancel()


class PinCallback:
    __slots__ = ["_cdata", "name"]

    def __init__(self, name: str) -> None:
        self._cdata = ffi.new_handle(self)
        self.name = name

    def __str__(self) -> str:
        return f"Pin(name={self.name!r})"

    def set_dir(self, output: bool) -> None:
        raise NotImplementedError()

    def write(self, state: bool) -> None:
        raise NotImplementedError()

    def read(self) -> bool:
        raise NotImplementedError()

    @property
    def cdata(self) -> cffi.FFI.CData:
        return self._cdata


@blinky_cffi.ffi.def_extern()
@spi_bitbang_cffi.ffi.def_extern()
def pin_set_dir(pin_ptr: cffi.FFI.CData, output: bool) -> None:
    void_ptr = ffi.cast("void *", pin_ptr)
    pin = cast(PinCallback, ffi.from_handle(void_ptr))
    pin.set_dir(output)


@blinky_cffi.ffi.def_extern()
@spi_bitbang_cffi.ffi.def_extern()
def pin_write(pin_ptr: cffi.FFI.CData, state: bool) -> None:
    void_ptr = ffi.cast("void *", pin_ptr)
    pin = cast(PinCallback, ffi.from_handle(void_ptr))
    pin.write(state)


@blinky_cffi.ffi.def_extern()
@spi_bitbang_cffi.ffi.def_extern()
def pin_read(pin_ptr: cffi.FFI.CData) -> bool:
    void_ptr = ffi.cast("void *", pin_ptr)
    pin = cast(PinCallback, ffi.from_handle(void_ptr))
    return pin.read()


PinCallbackFn = Optional[Callable[[], None]]


class Pin(PinCallback):
    __slots__ = ["dir_is_output", "output", "input", "on_rise", "on_fall"]

    def __init__(self, name: str,
                 on_rise: PinCallbackFn = None,
                 on_fall: PinCallbackFn = None) -> None:
        super().__init__(name)
        self.name = name
        self.dir_is_output = False
        self.output = False
        self.input = False
        self.on_rise = on_rise
        self.on_fall = on_fall

    def __str__(self) -> str:
        parts = [
            f"name={self.name!r}",
            f"dir_is_output={self.dir_is_output!r}",
            f"output={self.output!r}",
            f"input={self.input!r}",
        ]
        return "Pin(" + ", ".join(parts) + ")"

    def set_dir(self, output: bool) -> None:
        self.dir_is_output = output

    def write(self, state: bool) -> None:
        if not self.output and state and self.on_rise:
            self.on_rise()
        elif self.output and not state and self.on_fall:
            self.on_fall()
        self.output = state

    def read(self) -> bool:
        return self.input


class PinintOwner(NamedTuple):
    recipient: Actor
    rising_sig: Sig
    falling_sig: Sig


class Pinint:
    __slots__ = ["_cdata", "_owner", "name"]

    def __init__(self, name: str) -> None:
        self._cdata = ffi.new_handle(self)
        self._owner: Optional[PinintOwner] = None
        self.name = name

    def __str__(self) -> str:
        return f"Pinint(name={self.name!r})"

    def acquire(self, recipient: Actor, rising_sig: Sig, falling_sig: Sig) -> None:
        self._owner = PinintOwner(recipient, rising_sig, falling_sig)

    def trigger_rise(self) -> None:
        if self._owner:
            self._owner.recipient.post(self._owner.rising_sig)

    def trigger_fall(self) -> None:
        if self._owner:
            self._owner.recipient.post(self._owner.falling_sig)

    @property
    def cdata(self) -> cffi.FFI.CData:
        return self._cdata


@blinky_cffi.ffi.def_extern()
def pinint_acquire(pinint_ptr: cffi.FFI.CData,
                   recipient_ptr: cffi.FFI.CData,
                   rising_sig: Sig,
                   falling_sig: Sig) -> None:
    pinint_void_ptr = ffi.cast("void *", pinint_ptr)
    pinint = cast(Pinint, ffi.from_handle(pinint_void_ptr))
    recipient = ACTORS[recipient_ptr]
    pinint.acquire(recipient, rising_sig, falling_sig)


class Blinky:
    FLASH_PERIOD_MS = blinky_cffi.lib.BLINKY_FLASH_PERIOD_MS
    FLASH_COUNT = blinky_cffi.lib.BLINKY_FLASH_COUNT

    def __init__(self, button_pinint: Pinint, button_pin: Pin, led_pin: Pin) -> None:
        if not isinstance(button_pinint, Pinint):
            raise TypeError(button_pinint)
        if not isinstance(button_pin, Pin):
            raise TypeError(button_pin)
        if not isinstance(led_pin, Pin):
            raise TypeError(led_pin)
        self._cdata = blinky_cffi.ffi.new("struct blinky *")
        self._button_pinint = button_pinint
        self._button_pin = button_pin
        self._led_pin = led_pin
        blinky_cffi.lib.blinky_init(self._cdata, self._button_pinint.cdata, self._button_pin.cdata, self._led_pin.cdata)
        self._actor = get_last_actor()

    @property
    def button_pinint(self) -> Pinint:
        return self._button_pinint

    @property
    def button_pin(self) -> Pin:
        return self._button_pin

    @property
    def led_pin(self) -> Pin:
        return self._led_pin


class BitbangSpi:
    __slots__ = ["_cdata", "mosi", "sck", "ss"]

    def __init__(self, mosi: Pin, sck: Pin, ss: Pin) -> None:
        if not isinstance(mosi, Pin):
            raise TypeError(mosi)
        if not isinstance(sck, Pin):
            raise TypeError(sck)
        if not isinstance(ss, Pin):
            raise TypeError(ss)
        self._cdata = spi_bitbang_cffi.ffi.new("struct spi *")
        self.mosi = mosi
        self.sck = sck
        self.ss = ss
        spi_bitbang_cffi.lib.spi_bitbang_init(self._cdata, mosi._cdata, sck._cdata, ss._cdata)

    def write(self, data: int) -> None:
        spi_bitbang_cffi.lib.spi_write(self._cdata, data)
