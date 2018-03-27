#include <moss.h>

void _start() 
{
    uint16_t* video = (uint16_t*)0xB8000;
    char* str = "Hello world.";

    for(int i = 0; i < 5; i++)
    {
        video[i] = (str[i] | (0x0F << 8));
    }

    for(;;);
}
