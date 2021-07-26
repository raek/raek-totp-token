from typing import Callable, Optional, cast

import cffi  # type: ignore

import pure_cffi  # type: ignore
import inverter_cffi  # type: ignore
import spi_bitbang_cffi  # type: ignore


ffi = cffi.FFI()


datetime_is_valid = pure_cffi.lib.datetime_is_valid


def datetime_to_unix_time(year: int, month: int, day: int, hour: int, minute: int, second: int) -> Optional[int]:
    result = pure_cffi.ffi.new("UnixTime *", 0)
    if pure_cffi.lib.datetime_to_unix_time(result, year, month, day, hour, minute, second):
        return cast(int, result[0])
    else:
        return None


class Sha1:
    def __init__(self) -> None:
        self._cdata = pure_cffi.ffi.new("Sha1 *")
        pure_cffi.lib.sha1_init(self._cdata)

    def update(self, chunk: bytes) -> None:
        pure_cffi.lib.sha1_update(self._cdata, chunk, len(chunk))

    def digest(self) -> bytes:
        digest = pure_cffi.ffi.new("uint8_t[]", pure_cffi.lib.SHA1_DIGEST_BYTES)
        pure_cffi.lib.sha1_digest(self._cdata, digest)
        return bytes(digest)


def hmac_sha1(key: bytes, message: bytes) -> bytes:
    scratchpad = pure_cffi.ffi.new("HmacSha1 *")
    code = pure_cffi.ffi.new("uint8_t[]", pure_cffi.lib.HMAC_SHA1_CODE_BYTES)
    pure_cffi.lib.hmac_sha1(scratchpad, key, len(key), message, len(message), code)
    return bytes(code)


def hotp(secret: bytes, counter: int) -> str:
    scratchpad = pure_cffi.ffi.new("Hotp *")
    output = pure_cffi.ffi.new("char[]", pure_cffi.lib.HOTP_DIGITS)
    pure_cffi.lib.hotp(scratchpad, secret, len(secret), counter, output)
    return cast(bytes, pure_cffi.ffi.string(output)).decode("ascii")


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


@inverter_cffi.ffi.def_extern()
@spi_bitbang_cffi.ffi.def_extern()
def pin_set_dir(pin_ptr: cffi.FFI.CData, output: bool) -> None:
    void_ptr = ffi.cast("void *", pin_ptr)
    pin = cast(PinCallback, ffi.from_handle(void_ptr))
    pin.set_dir(output)


@inverter_cffi.ffi.def_extern()
@spi_bitbang_cffi.ffi.def_extern()
def pin_write(pin_ptr: cffi.FFI.CData, state: bool) -> None:
    void_ptr = ffi.cast("void *", pin_ptr)
    pin = cast(PinCallback, ffi.from_handle(void_ptr))
    pin.write(state)


@inverter_cffi.ffi.def_extern()
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


class Inverter:
    def __init__(self, in_pin: Pin, out_pin: Pin) -> None:
        if not isinstance(in_pin, Pin):
            raise TypeError(in_pin)
        if not isinstance(out_pin, Pin):
            raise TypeError(out_pin)
        self._cdata = inverter_cffi.ffi.new("Inverter *")
        self._in_pin = in_pin
        self._out_pin = out_pin
        inverter_cffi.lib.inverter_init(self._cdata, self._in_pin.cdata, self._out_pin.cdata)

    @property
    def in_pin(self) -> Pin:
        return self._in_pin

    @property
    def out_pin(self) -> Pin:
        return self._out_pin

    def run(self) -> None:
        inverter_cffi.lib.inverter_run(self._cdata)


class BitbangSpi:
    __slots__ = ["_cdata", "mosi", "sck", "ss"]

    def __init__(self, mosi: Pin, sck: Pin, ss: Pin) -> None:
        if not isinstance(mosi, Pin):
            raise TypeError(mosi)
        if not isinstance(sck, Pin):
            raise TypeError(sck)
        if not isinstance(ss, Pin):
            raise TypeError(ss)
        self._cdata = spi_bitbang_cffi.ffi.new("Spi *")
        self.mosi = mosi
        self.sck = sck
        self.ss = ss
        spi_bitbang_cffi.lib.spi_bitbang_init(self._cdata, mosi._cdata, sck._cdata, ss._cdata)

    def write(self, data: int) -> None:
        spi_bitbang_cffi.lib.spi_write(self._cdata, data)
