#include <keyboard.h>

uint8_t kbdus[128] = {
    0, 0, '1', '2', '3', '4', '5', '6', 
    '7', '8', '9', '0', '-', '=', 0, 0,
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 
    'o', 'p', '[', ']', 0, 0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l',
    ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 
    'v', 'b', 'n', 'm', ',', '.', '/', 0,
    0, 0, 0, ' ', 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0
};

uint8_t kbdus_mod[128] = {
    0, 0, '!', '@', '#', '$', '%', '^', 
    '&', '*', '(', ')', '_', '+', 0, 0,
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 
    'O', 'P', '{', '}', 0, 0, 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L',
    ':', '"', '~', 0, '|', 'Z', 'X', 'C', 
    'V', 'B', 'N', 'M', '<', '>', '?', 0,
    0, 0, 0, ' ', 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0
};

void* keyboard_handlers[16] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
};

// https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html

uint8_t shift = 0;
void keyboard_handle(struct registers_t* r)
{
    uint8_t scancode = in8(0x60);
    // TODO: if we get an escape scancode, set an internal flag which 
    // TODO: will effect the next key which uses the escape, it should
    // TODO: then reset the flag.

    // TODO: key struct

    // 0 = key pressed
    // 1 = key released
    uint8_t state = (scancode & 0b10000000) >> 7;

    if(scancode == 0x2A)
    {
        shift = 1;
    }
    if(scancode == 0xAA)
    {
        shift = 0;
    } 

    scancode &= ~(1 << 7);

    uint8_t ascii = 0;
    if(shift)
    {
        ascii = kbdus_mod[scancode];
    }
    else
    {
        ascii = kbdus[scancode];
    }

    struct key_t* key = (struct key_t*)malloc(sizeof(struct key_t));
    key->scancode = scancode;
    key->pressed = !state;
    key->ascii = ascii;

    // TODO: Do stuff with the key.
    //if(key->pressed) {
    //    printf("%c", key->ascii);
    //}

    void (*handler)(struct key_t* key);
    for(int i = 0; i < 16; i++)
    {
        handler = keyboard_handlers[i];
        if(handler)
        {
            handler(key);
        }
    }

    free(key);
}

void init_keyboard()
{
    irq_add_hook(1, keyboard_handle);
}

void keyboard_add_handler(int id, void* handler)
{
    keyboard_handlers[id] = handler;
}
