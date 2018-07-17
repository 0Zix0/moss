#include <string.h>

void* memset(void* bufptr, int value, size_t size) {
	unsigned char* buf = (unsigned char*) bufptr;
	for (size_t i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;
}

void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size) {
    unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}

int strlen(char* str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		i++;
	}
	return i;
}

int strcmp(const char* str1, const char* str2)
{
   int res=0;
   while(!(res=*(unsigned char*)str1-*(unsigned char*)str2) && *str2){
      ++str1;
      ++str2;
   }
   
   if (res<0) res=-1;
   if (res>0) res=1;

   return res;
}
