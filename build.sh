#!/bin/bash

echo Build Started...

build_asm() {
    nasm -f bin -o out/$2 src/$1
}

build_asm_elf() {
    nasm -f elf -o out/$2 src/$1
}

build_c() {
    gcc -fno-builtin -fno-stack-protector -m32 -c -I./include -o out/$2 src/$1
}

link() {
    cp linker.ld out
    cd out
    mkdir -p link
    ld -T linker.ld --oformat binary -m elf_i386 -Ttext 1000 $1 -o link/$2
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

echo Compiling...

build_asm asm/boot.asm boot
build_asm_elf asm/gdtload.asm gdtload
build_asm_elf asm/idtload.asm idtload
build_asm_elf asm/interruptstubs.asm isrstubs
build_asm_elf asm/irqstubs.asm irqstubs

build_c moss.c moss

build_c drivers/vga.c vga
build_c drivers/printf.c printf
build_c drivers/shell.c shell
build_c drivers/gdt.c gdt
build_c drivers/idt.c idt
build_c drivers/isrs.c isrs
build_c drivers/irq.c irq
build_c drivers/timer.c timer
build_c drivers/keyboard.c keyboard
build_c drivers/paging.c paging
build_c drivers/malloc.c malloc
build_c drivers/pci.c pci
build_c drivers/acpi.c acpi

build_c hal/ports.c ports

build_c debug/assert.c assert

build_c util/string.c string
build_c util/crash.c crash
build_c util/random.c random

echo Linking...

link "moss string crash random vga printf ports gdt gdtload idt 
idtload isrs isrstubs irq irqstubs timer keyboard paging malloc 
pci acpi assert shell" kernel

echo Creating floppy image...

create_floppy "boot link/kernel" floppy.img

clean

echo Build finished.
