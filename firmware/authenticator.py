from argparse import ArgumentParser
from base64 import b32decode
from time import time

from firmware import hotp


def totp(secret_b32: str, interval: int = 30) -> str:
    secret = b32decode(secret_b32)
    t = int(time()) // interval
    return hotp(secret, t)


def read_secret(path: str) -> str:
    with open(path, "rt") as f:
        unpadded_b32 = f.readline().strip()
    padded_b32 = unpadded_b32 + ("=" * (8 - len(unpadded_b32) % 8))
    return padded_b32


def main() -> None:
    parser = ArgumentParser()
    parser.add_argument("secret_file")
    args = parser.parse_args()
    secret_b32 = read_secret(args.secret_file)
    token = totp(secret_b32)
    print(token)


if __name__ == "__main__":
    main()
