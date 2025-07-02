

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

char *strchrnul(char *s, int c)
{
	char *res = strchr(s, c);
	if (!res)
		return s + strlen(s);
	return res;
}

#endif

#define mstrcpy(src) strcpy(mallocadd(strlen(src) + 1), src)

#define strrstr strlaststr
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

void memrpl(char *dst, char c, int n, char original)
{
	for (int i = 0; i < n; ++i)
		if (dst[i] == original)
			dst[i] = c;
}

void strrpl(char *dst, char c, char original)
{
	for (int i = 0; dst[i]; ++i)
		if (dst[i] == original)
			dst[i] = c;
}
