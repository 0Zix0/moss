#include <crash.h>

void assert_failed(char* file, int line, char* expr)
{
    cls();
    printf("Assetion failed [%s] at %s, line %d\n", expr, file, line);
    while(1);
}

void system_exception(char* msg, struct registers_t* r)
{
    cls();
    int len = strlen(msg);
    len += 2;
    int xPos = 40 - (len / 2);
    set_cursor_pos(xPos, 1);
    set_color(VGA_DARK_GRAY, VGA_BLACK);
    printf("[");
    set_color(VGA_LIGHT_RED, VGA_BLACK);
    printf("%s", msg);
    set_color(VGA_DARK_GRAY, VGA_BLACK);
    printf("]\n");

    char* msg1 = "THE OPERATING SYSTEM HAS ENCOUNTERED A FATAL ERROR";
    char* msg2 = "FROM WHICH IT CAN NOT RECOVER. IF YOU ARE NOT AT";
    char* msg3 = "FAULT, CONTACT A DEVELOPER.";

    int msg1X = 40 - (strlen(msg1) / 2);
    int msg2X = 40 - (strlen(msg2) / 2);
    int msg3X = 40 - (strlen(msg3) / 2);

    set_color(VGA_WHITE, VGA_BLACK);
    set_cursor_pos(msg1X, 3);
    printf("%s", msg1);
    set_cursor_pos(msg2X, 4);
    printf("%s", msg2);
    set_cursor_pos(msg3X, 5);
    printf("%s", msg3);
    putc('\n');

    set_cursor_pos(27, 7);
    printf("gs:  %x fs:  %x\n", r->gs, r->fs);
    set_cursor_pos(27, 8);
    printf("es:  %x ds:  %x\n", r->es, r->ds);
    set_cursor_pos(27, 9);
    printf("edi: %x esi: %x\n", r->edi, r->esi);
    set_cursor_pos(27, 10);
    printf("ebp: %x esp: %x\n", r->ebp, r->esp);
    set_cursor_pos(27, 11);
    printf("ecx: %x eax: %x\n", r->ecx, r->eax);
    set_cursor_pos(34, 12);
    printf("eip: %x\n", r->eip);
    set_cursor_pos(34, 13);
    printf("cs:  %x\n", r->cs);
    set_cursor_pos(34, 14);
    printf("ss:  %x\n", r->ss);
    set_cursor_pos(32, 15);
    printf("eflags:  %x\n", r->eflags);
    set_cursor_pos(32, 16);
    printf("useresp: %x\n", r->useresp);
}

void system_catch_fire()
{
    char* characters = "#$Ss*:.";
    int intensities[7] = {
        32767 * 0.9f,
        32767 * 0.8f,
        32767 * 0.75f,
        32767 * 0.5f,
        32767 * 0.25f,
        32767 * 0.18f,
        32767 * 0.1f
    };
    uint8_t colors[7] = {
        VGA_RED,
        VGA_RED,
        VGA_RED,
        VGA_LIGHT_RED,
        VGA_LIGHT_RED,
        VGA_LIGHT_RED,
        VGA_WHITE
    };

    int tick = 0;
    while(1)
    {
        //if(tick % 6562500 == 0)
        //{
        for(int i = 0; i < 7; i++)
        {
            char* line = "                                                                                ";
            for(int j = 0; j < 80; j++)
            {
                int r = rand();
                if(r < intensities[i]) {
                    line[j] = characters[i];
                } else {
                    line[j] = ' ';
                }
            }
            set_cursor_pos(0, 24 - i);
            for(int j = 0; j < 80; j++)
            {
                set_color(colors[i], VGA_BLACK);
                    if(i == 2)
                    {
                        int r = rand();
                        if(r < RAND_MAX / 2)
                        {
                            set_color(VGA_LIGHT_RED, VGA_BLACK);
                        }
                    }
                    putc(line[j]);
                }
            }
        //}
        tick++;
    }
}
