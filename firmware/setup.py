from distutils.core import setup, Extension

firmware = Extension(
    "firmware",
    sources=[
        "firmware.c",
        "datetime.c",
        "datetime_py.c",
    ])

setup(
    name="raek-totp-token",
    version="0.0.1",
    description="Raek's TOTP hardware token",
    ext_modules=[firmware])
