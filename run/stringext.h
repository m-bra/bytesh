#include "main.h"

#ifndef STRINGEXTH
#define STRINGEXTH

char *memcmov(char *dst, char *src, int c, size_t n);

char *strnmov(char *dst, char *src, size_t n);

#ifdef DEFSTRCHRNUL

char *strchrnul(char *sz, int c);

#endif

#define mstrcpy(src) strcpy(mallocadd(strlen(src) + 1), src)

#define strrstr strlaststr
char *strlaststr(char *haystack, char *needle);

void memrpl(char *dst, char c, int n, char original);
void strrpl(char *dst, char c, char original);

#endif
