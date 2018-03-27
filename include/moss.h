#ifndef _MOSS_H
#define _MOSS_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned int size_t;

struct registers_t {
    int32_t gs, fs, es, ds;
    int32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    int32_t int_no, err_code;
    int32_t eip, cs, eflags, useresp, ss;
};

#endif
