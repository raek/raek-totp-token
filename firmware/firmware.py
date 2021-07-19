from typing import Optional, cast

from firmware_cffi import ffi, lib  # type: ignore


datetime_is_valid = lib.datetime_is_valid


def datetime_to_unix_time(year: int, month: int, day: int, hour: int, minute: int, second: int) -> Optional[int]:
    result = ffi.new("UnixTime *", 0)
    if lib.datetime_to_unix_time(result, year, month, day, hour, minute, second):
        return cast(int, result[0])
    else:
        return None


class Sha1:
    DIGEST_BYTES = 20  # TODO: extract from header

    def __init__(self) -> None:
        self._cdata = ffi.new("Sha1 *")
        lib.sha1_init(self._cdata)

    def update(self, chunk: bytes) -> None:
        lib.sha1_update(self._cdata, chunk, len(chunk))

    def digest(self) -> bytes:
        digest = ffi.new("uint8_t[]", self.DIGEST_BYTES)
        lib.sha1_digest(self._cdata, digest)
        return bytes(digest)


def hmac_sha1(key: bytes, message: bytes) -> bytes:
    CODE_BYTES = Sha1.DIGEST_BYTES
    scratchpad = ffi.new("HmacSha1 *")
    code = ffi.new("uint8_t[]", CODE_BYTES)
    lib.hmac_sha1(scratchpad, key, len(key), message, len(message), code)
    return bytes(code)


def hotp(secret: bytes, counter: int) -> str:
    HOTP_DIGITS = 6  # TODO: extract from header
    scratchpad = ffi.new("Hotp *")
    output = ffi.new("char[]", HOTP_DIGITS)
    lib.hotp(scratchpad, secret, len(secret), counter, output)
    return b"".join(output).decode("ascii")


class Pin:
    __slots__ = ["_cdata", "name", "dir_is_output", "output", "input"]

    def __init__(self, name: str) -> None:
        self._cdata = ffi.new_handle(self)
        self.name = name
        self.dir_is_output = False
        self.output = False
        self.input = False

    def __str__(self) -> str:
        parts = [
            f"name={self.name!r}",
            f"dir_is_output={self.dir_is_output!r}",
            f"output={self.output!r}",
            f"input={self.input!r}",
        ]
        return "Pin(" + ", ".join(parts) + ")"

    @property
    def cdata(self) -> ffi.CData:
        return self._cdata


@ffi.def_extern()
def pin_set_dir(pin_ptr: ffi.CData, output: bool) -> None:
    void_ptr = ffi.cast("void *", pin_ptr)
    pin = cast(Pin, ffi.from_handle(void_ptr))
    pin.dir_is_output = output


@ffi.def_extern()
def pin_write(pin_ptr: ffi.CData, state: bool) -> None:
    void_ptr = ffi.cast("void *", pin_ptr)
    pin = cast(Pin, ffi.from_handle(void_ptr))
    pin.output = state


@ffi.def_extern()
def pin_read(pin_ptr: ffi.CData) -> bool:
    void_ptr = ffi.cast("void *", pin_ptr)
    pin = cast(Pin, ffi.from_handle(void_ptr))
    return pin.input


class Inverter:
    def __init__(self, in_pin: Pin, out_pin: Pin) -> None:
        if not isinstance(in_pin, Pin):
            raise TypeError(in_pin)
        if not isinstance(out_pin, Pin):
            raise TypeError(out_pin)
        self._cdata = ffi.new("Inverter *")
        self._in_pin = in_pin
        self._out_pin = out_pin
        lib.inverter_init(self._cdata, self._in_pin.cdata, self._out_pin.cdata)

    @property
    def in_pin(self) -> Pin:
        return self._in_pin

    @property
    def out_pin(self) -> Pin:
        return self._out_pin

    def run(self) -> None:
        lib.inverter_run(self._cdata)
