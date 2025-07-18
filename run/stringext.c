#include "main.h"


char *memcmov(char *dst, char *src, int c, size_t n)
{
	char tmp[n];
	        memccpy(tmp, src, c, n);
	return  memccpy(dst, tmp, c, n);
}

char *strnmov(char *dst, char *src, size_t n)
{
	return memcmov(dst, src, 0, n);
}

#ifdef DEFSTRCHRNUL

char *strchrnul(char *sz, int c)
{
	char *res = strchr(sz, c);
	if (!res)
		return sz + strlen(sz);
	return res;
}

#endif

char *strlaststr(char *haystack, char *needle)
{
	char *q = 0;
	char *p = haystack;
	while ((p = strstr(p, needle)))
	{
		q = p;
		p += strlen(needle);
	}
	return q;
}

SECTION TEXT

FUNCTION void memrpl(char *dst, char c, int n, char original)

def
for (int i = 0; i < n; ++i)
iff dst[i] == original
thn dst[i] = c;

FUNCTION inline void strrpl(char *dst, char c, char original)

def
for (int i = 0; dst[i]; ++i)
iff dst[i] == original
thn dst[i] = c;

SECTION DATA
