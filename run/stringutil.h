
char *escapeccstr(char *s, int buflen, int c, int r)
{
	if (buflen < (int)strlen(s) * 2)
	{
		printf("Error at %s:%d\n", __FILE__, __LINE__);
		exit(1);	
	}

    char *p = s;
    char *end = p + strlen(p);
    while ((p = strchrnul(p, c)) != end)
    {
    	strnmov(p + 1, p, buflen);
    	p[0] = '\\';
    	p[1] = r;
    	p+= 2;
    	end = p + strlen(p);
    }
	return s;
}
