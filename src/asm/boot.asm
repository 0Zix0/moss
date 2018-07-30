%define BASE 0x100
%define KSIZE 50

;
; README
; http://www.cs.cmu.edu/~410-s07/p4/p4-boot.pdf
; https://wiki.osdev.org/Rolling_Your_Own_Bootloader
; http://3zanders.co.uk/2017/10/13/writing-a-bootloader/
; Redesign bootloader for version 2.
; Bootloader should pass valuable info to the kernel.
;

[BITS 16]
[ORG 0x0]

jmp start

; Procedure for printing strings.
; Example usage:
;   mov si, myString
;   call print
;   myString: db "Hello, world.", 13, 10, 0
print:
    push ax
    push bx
.printLoop:
    lodsb
    cmp al, 0
    jz .printEnd
    mov ah, 0x0E
    mov bx, 0x07
    int 0x10
    jmp .printLoop

.printEnd:
    pop bx
    pop ax
    ret

; Bootloader main
; Resposible for;
;   Loading kernel into memory.
;   Setting up GDT.
;   Entering protected mode.
;   Jumping to the newly loaded kernel.
start:
    mov ax, 0x07C0
    mov ds, ax
    mov es, ax
    mov ax, 0x8000
    mov ss, ax
    mov sp, 0xF000

    mov [bootdrv], dl

    mov si, msgBoot
    call print

    ; 
    ; Switches into 1024x768x32bpp VESA mode
    ; See https://wiki.osdev.org/User:Omarrx024/VESA_Tutorial
    ;
    ; BX - Bits 0-13 mode number; bit 14 is the LFB bit: when set, it 
    ;      enables the linear framebuffer, when clear, software must 
    ;      use bank switching. Bit 15 is the DM bit: when set, the BIOS 
    ;      doesn't clear the screen. Bit 15 is usually ignored and should 
    ;      always be cleared. 
    ;      1024x768x32bpp = mode 0x0118
    ;
    ; In order to actually make use of this, we will need to read the VBE
    ; Mode Info block, as this contains the actual address of the framebuffer
    ; which we need to write to in order to draw.
    ; I imagine that we would do this on boot and pass this structure to the
    ; kernel.
    ;
    ; mov ax, 0x4F02	; Function 0x4F02 refers to Set VBE Mode
    ; mov bx, 0x4118	; VBE mode number; notice that bits 0-13 contain the mode number and bit 14 (LFB) is set and bit 15 (DM) is clear.
    ; int 0x10
    ;
    ; Maybe we could move this somewhere else, or call it from the C code.
    ;
    xor ax, ax
    int 0x13

    push es
    mov ax, BASE
    mov es, ax
    mov bx, 0
    mov ah, 2
    mov al, KSIZE
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, [bootdrv]
    int 0x13
    pop es

    mov ax, gdtend
    mov bx, gdt
    sub ax, bx
    mov word [gdtptr], ax

    xor eax, eax
    xor ebx, ebx
    mov ax, ds
    mov ecx, eax
    shl ecx, 4
    mov bx, gdt
    add ecx, ebx
    mov dword [gdtptr + 2], ecx

    cli
    lgdt [gdtptr]
    mov eax, cr0
    or ax, 1
    mov cr0, eax

    jmp next
next:
    mov ax, 0x10
    mov ds, ax
    mov fs, ax
    mov gs, ax
    mov es, ax
    mov ss, ax
    mov esp, 0x9F000

    ; Write 0x52 to address 0x0600.
    ; This can be accessed from the kernel.
    mov ebx, 0x0600
    mov ax, 0x52
    mov [ebx], ax

    jmp dword 0x8:0x1000

bootdrv: db 0
msgBoot: db "Booting...", 13, 10, 0

gdt:
    db 0, 0, 0, 0, 0, 0, 0, 0
gdt_cs:
    db 0xFF, 0xFF, 0x0, 0x0, 0x0, 10011011b, 11011111b, 0x0
gdt_ds:
    db 0xFF, 0xFF, 0x0, 0x0, 0x0, 10010011b, 11011111b, 0x0
gdtend:

gdtptr:
    dw 0
    dd 0

times 510 - ($ - $$) db 144
dw 0xAA55
