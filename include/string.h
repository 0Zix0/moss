#ifndef _STRING_H
#define _STRING_H

#include <moss.h>

void* memset(void* bufptr, int value, size_t size);
void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size);
int strlen(char* str);

#endif