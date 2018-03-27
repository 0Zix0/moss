#!/bin/bash

echo Build Started...

build_asm() {
    nasm -f bin -o out/$2 src/$1
}

build_asm_elf() {
    nasm -f elf -o out/$2 src/$1
}

build_c() {
    gcc -fno-builtin -m32 -c -I./include -o out/$2 src/$1
}

link() {
    cd out
    mkdir -p link
    ld --oformat binary -m elf_i386 -Ttext 1000 $1 -o link/$2
    cd ..
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
build_asm_elf gdtload.asm gdtload
build_asm_elf idtload.asm idtload

build_c moss.c moss
build_c vga.c vga
build_c ports.c ports
build_c gdt.c gdt
build_c idt.c idt

echo Linking...
link "moss vga ports gdt gdtload idt idtload" kernel

create_floppy "boot link/kernel" floppy

clean

echo Build finished.
