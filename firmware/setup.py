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
        "datetime_pywrap.c",
        "pin_pyimpl.c",
        "inverter.c",
        "inverter_pywrap.c",
        "sha1.c",
        "sha1_pywrap.c",
        "hmac_sha1.c",
        "hmac_sha1_pywrap.c",
        "hotp.c",
        "hotp_pywrap.c",
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
