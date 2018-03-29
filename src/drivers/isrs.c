#include <isrs.h>

extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();

void init_isrs()
{
    set_idt_entry(0, (unsigned)_isr0, 0x08, 0x8E);
    set_idt_entry(1, (unsigned)_isr1, 0x08, 0x8E);
    set_idt_entry(2, (unsigned)_isr2, 0x08, 0x8E);
    set_idt_entry(3, (unsigned)_isr3, 0x08, 0x8E);
    set_idt_entry(4, (unsigned)_isr4, 0x08, 0x8E);
    set_idt_entry(5, (unsigned)_isr5, 0x08, 0x8E);
    set_idt_entry(6, (unsigned)_isr6, 0x08, 0x8E);
    set_idt_entry(7, (unsigned)_isr7, 0x08, 0x8E);
    set_idt_entry(8, (unsigned)_isr8, 0x08, 0x8E);
    set_idt_entry(9, (unsigned)_isr9, 0x08, 0x8E);
    set_idt_entry(10, (unsigned)_isr10, 0x08, 0x8E);
    set_idt_entry(11, (unsigned)_isr11, 0x08, 0x8E);
    set_idt_entry(12, (unsigned)_isr12, 0x08, 0x8E);
    set_idt_entry(13, (unsigned)_isr13, 0x08, 0x8E);
    set_idt_entry(14, (unsigned)_isr14, 0x08, 0x8E);
    set_idt_entry(15, (unsigned)_isr15, 0x08, 0x8E);
    set_idt_entry(16, (unsigned)_isr16, 0x08, 0x8E);
    set_idt_entry(17, (unsigned)_isr17, 0x08, 0x8E);
    set_idt_entry(18, (unsigned)_isr18, 0x08, 0x8E);
    set_idt_entry(19, (unsigned)_isr19, 0x08, 0x8E);
    set_idt_entry(20, (unsigned)_isr20, 0x08, 0x8E);
    set_idt_entry(21, (unsigned)_isr21, 0x08, 0x8E);
    set_idt_entry(22, (unsigned)_isr22, 0x08, 0x8E);
    set_idt_entry(23, (unsigned)_isr23, 0x08, 0x8E);
    set_idt_entry(24, (unsigned)_isr24, 0x08, 0x8E);
    set_idt_entry(25, (unsigned)_isr25, 0x08, 0x8E);
    set_idt_entry(26, (unsigned)_isr26, 0x08, 0x8E);
    set_idt_entry(27, (unsigned)_isr27, 0x08, 0x8E);
    set_idt_entry(28, (unsigned)_isr28, 0x08, 0x8E);
    set_idt_entry(29, (unsigned)_isr29, 0x08, 0x8E);
    set_idt_entry(30, (unsigned)_isr30, 0x08, 0x8E);
    set_idt_entry(31, (unsigned)_isr31, 0x08, 0x8E);
}

char* exceptions[32] = {
    "DIVIDE BY ZERO",
    "DEBUG",
    "NON-MASKABLE INTERRUPT",
    "BREAKPOINT",
    "OVERFLOW",
    "BOUND RANGE EXCEEDED",
    "INVALID OPCODE",
    "DEVICE NOT AVAILABLE",
    "DOUBLE FAULT",
    "COPROCESSOR SEGMENT OVERRUN",
    "INVALID TSS",
    "SEGMENT NOT PRESENT",
    "STACK-SEGMENT FAULT",
    "GENERAL PROTECTION FAULT",
    "PAGE FAULT",
    "RESERVED",
    "FLOATING-POINT EXCEPTION (x87)",
    "ALIGNMENT CHECK",
    "FLOATING-POINT EXCEPTION (SIMD)",
    "VIRTUALIZATION EXCEPTION",
    "RESERVED",
    "SECURITY EXCEPTION",
    "RESERVED"
};

void fault_handler(struct registers_t* r)
{
    if(r->int_no < 32) 
    {
        cls();
        int len = strlen(exceptions[r->int_no]);
        len += 2;
        int xPos = 40 - (len / 2);
        set_cursor_pos(xPos, 1);
        set_color(VGA_DARK_GRAY, VGA_BLACK);
        printf("[");
        set_color(VGA_LIGHT_RED, VGA_BLACK);
        printf("%s", exceptions[r->int_no]);
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

        // RAND_MAX = 32767
        char* characters = "$#Ss*:.";
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
            if(tick % 6562500 == 0)
            {
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
            }
            tick++;
        }

        while(1);
    }
}
