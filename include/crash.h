#ifndef _CRASH_H
#define _CRASH_H

#include <moss.h>
#include <idt.h>
#include <vga.h>
#include <string.h>
#include <random.h>

void system_exception(char* msg, struct registers_t* r);
void system_catch_fire();

#endif