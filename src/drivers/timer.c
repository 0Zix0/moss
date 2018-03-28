#include <timer.h>

void timer_handle(struct registers_t* r);

void init_timer()
{
    timer_set(1000);
    irq_add_hook(0, timer_handle);
}

void timer_set(int hz)
{
    int divisor = 1193180 / hz;
    out8(0x43, 0x36);
    out8(0x40, divisor & 0xFF);
    out8(0x40, divisor >> 8);
}

uint64_t ticks;
void timer_handle(struct registers_t* r)
{
    ticks++;
    //putc('t');
}
