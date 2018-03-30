#ifndef _ASSERT_H
#define _ASSERT_H

#include <moss.h>
#include <crash.h>
#include <vga.h>

#if MOSS_DEBUG
#define assert(expr) ((expr) ? (void)0 : assert_failed(__FILE__, __LINE__, #expr))
#else
#define assert(expr)
#endif

void assert_failed(char* file, int line, char* expr);

#endif
