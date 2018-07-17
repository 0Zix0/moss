#include <shell.h>

uint8_t buffer[512];
uint32_t bufferSize = 0;

void key_event(struct key_t* key)
{
    if(key->pressed)
    {
        // Enter.
        if(key->scancode == 0x1C)
        {
            // Throw in a new-line so command output shows on the next line.
            printf("\n");
            uint8_t* cmd = malloc(bufferSize + 1);
            memcpy(cmd, buffer, bufferSize);
            cmd[bufferSize] = '\0';

            if(!strcmp(cmd, "cls"))
            {
                cls();
            } 
            else if(!strcmp(cmd, "crash"))
            {
                // Trigger divide by 0.
                int a = 10;
                int b = 0;
                int c = a / b;
            } 
            else if(!strcmp(cmd, "pci"))
            {
                pci_print_devices();
            } 
            else 
            {
                printf("Command not found.");
            }
            
            free(cmd);

            bufferSize = 0;

            printf("\n>");
        }
        // Backspace.
        if(key->scancode == 0x0E)
        {
            if(bufferSize != 0)
            {
                bufferSize--;
                set_cursor_pos(get_cursor_x() - 1, get_cursor_y());
                printf(" ");
                set_cursor_pos(get_cursor_x() - 1, get_cursor_y());
            }
        }
        if(key->ascii)
        {
            buffer[bufferSize] = key->ascii;
            bufferSize++;
            printf("%c", key->ascii);
        }
    }
}

void shell_start()
{
    cls();
    enable_cursor();
    puts("Welcome to ");
    set_color(VGA_GREEN, VGA_BLACK);
    puts("Moss");
    set_color(VGA_WHITE, VGA_BLACK);
    puts(".\n");
    printf(">");
    keyboard_add_handler(0, key_event);
    for(;;)
    {

    }
}