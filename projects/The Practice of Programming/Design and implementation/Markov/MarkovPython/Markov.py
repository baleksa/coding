#!/bin/python3
import random
import sys
from enum import Enum
from typing import TextIO


class Hash_type(Enum):
    JOINED = 0
    EACH = 1
    SEP = 2
    TUPLE = 3


NPREF: int = 2
NONWORD: str = "\n"
MAXGEN: int = 10000

stetab: dict[int, list[str]] = {}


def hash_prefix(code: Hash_type, prefix: list[str]):
    match code:
        case Hash_type.JOINED:
            return hash_joined(prefix)
        case Hash_type.EACH:
            return hash_each(prefix)
        case Hash_type.SEP:
            return hash_sep(prefix)
        case Hash_type.TUPLE:
            return hash_tuple(prefix)
        case _:
            exit(1)


def hash_tuple(prefix: list[str]):
    return tuple(word for word in prefix)


def hash_each(prefix: list[str]):
    p = 31
    h = 0
    for word in prefix:
        for char in word:
            h = h * p + hash(char)
    return h


def hash_joined(prefix: list[str]):
    return "".join(prefix)


def hash_sep(prefix: list[str]):
    h = 0
    for word in prefix:
        h += hash(word)


def build(istream: TextIO):
    prefix = [NONWORD for _ in range(NPREF)]
    for word in istream.read().split():
        add(prefix, word)
    add(prefix, NONWORD)


hash_type = Hash_type.TUPLE


def add(prefix: list[str], word: str):
    prefix_hash = hash_prefix(hash_type, prefix)
    if prefix_hash not in stetab:
        stetab[prefix_hash] = []
    stetab[prefix_hash].append(word)
    del prefix[0]
    prefix.append(word)


def generate(nword: int):
    prefix = [NONWORD for _ in range(NPREF)]
    for _ in range(nword):
        prefix_hash = hash_prefix(hash_type, prefix)
        if prefix_hash not in stetab:
            with open("outfile.txt", "w") as ofile:
                for item in stetab.items():
                    ofile.write(str(item) + "\n")
            print(prefix)
            print(prefix_hash)
            return
        sufices = stetab[prefix_hash]
        word = random.choice(sufices)
        if (word == NONWORD):
            return
        print(word)
        del prefix[0]
        prefix.append(word)


def main():
    build(sys.stdin)
    generate(MAXGEN)


if __name__ == "__main__":
    main()
