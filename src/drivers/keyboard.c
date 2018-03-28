#include <keyboard.h>

void keyboard_handle(struct registers_t* r);    

void init_keyboard()
{
    irq_add_hook(1, keyboard_handle);
}

void keyboard_handle(struct registers_t* r)
{
    putc(in8(0x60));
}
