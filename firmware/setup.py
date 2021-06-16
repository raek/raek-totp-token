from distutils.core import setup, Extension

firmware = Extension(
    "firmware",
    define_macros=[
        ("PY_SSIZE_T_CLEAN", None),
    ],
    extra_compile_args=[
        "-Wall",
        "-Wextra",
        "-Werror",
        "-Wno-unused-parameter",
        "-Og",
        "--coverage",
    ],
    extra_link_args=[
        "--coverage",
    ],
    sources=[
        "firmware.c",
        "datetime.c",
        "datetime_py.c",
        "pin_py.c",
        "inverter.c",
        "inverter_py.c",
        "sha1.c",
        "sha1_py.c",
        "hmac_sha1.c",
        "hmac_sha1_py.c",
        "hotp.c",
        "hotp_py.c",
    ])

setup(
    name="raek-totp-token",
    version="0.0.1",
    description="Raek's TOTP hardware token",
    ext_modules=[firmware],
    entry_points={
        "console_scripts": [
          "raek-auth = authenticator:main"
        ],
    })
