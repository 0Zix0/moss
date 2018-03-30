#ifndef _CRASH_H
#define _CRASH_H

#include <moss.h>
#include <idt.h>
#include <vga.h>
#include <string.h>
#include <random.h>

#if MOSS_DEBUG
#define assert(expr) ((expr) ? (void)0 : assert_failed(__FILE__, __LINE__, #expr))
#else
#define assert(expr)
#endif

void assert_failed(char* file, int line, char* expr);

void system_exception(char* msg, struct registers_t* r);
void system_catch_fire();

#endif