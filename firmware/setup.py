from distutils.core import setup, Extension

firmware = Extension(
    "firmware",
    define_macros=[
        ("PY_SSIZE_T_CLEAN", None),
    ],
    sources=[
        "firmware.c",
        "datetime.c",
        "datetime_py.c",
        "pin_py.c",
        "inverter.c",
        "inverter_py.c",
    ])

setup(
    name="raek-totp-token",
    version="0.0.1",
    description="Raek's TOTP hardware token",
    ext_modules=[firmware])
