#!/bin/bash

echo Build Started...

build_asm() {
    nasm -f bin -o out/$2 src/$1
}

create_floppy() {
    cd out
    cat $1 /dev/zero | dd of=../$2 bs=512 count=2880c
    cd ..
}

clean() {
    rm -r out
}

mkdir -p out

build_asm boot.asm boot
build_asm kernel.asm kernel

create_floppy "boot kernel" floppy

clean

echo Build finished.
