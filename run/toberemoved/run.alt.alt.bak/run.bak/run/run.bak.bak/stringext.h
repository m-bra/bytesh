
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

char *strchrnul(char *s, int c)
{
	char *res = strchr(s, c);
	if (!res)
		return s + strlen(s);
	return res;
}
