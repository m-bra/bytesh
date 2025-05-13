#ifndef RUN_STRINGUTIL_H_INCLUDED
#define RUN_STRINGUTIL_H_INCLUDED

#include "main.h"

char *escapeccstr(char *s, int buflen, int c, int r)
{
	if (buflen < (int)strlen(s) * 2) goto error;

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

error:
	printf("Error at %s:%d\n", __FILE__, __LINE__);
	exit(1);
}

char *escapecstr(char *s, int buflen)
{
    if (buflen < (int)strlen(s) * 2 * 2 * 2) goto error;
	s = escapeccstr(s, buflen, '\\', '\\');
	s = escapeccstr(s, buflen, '\"', '\"');
	s = escapeccstr(s, buflen, '\n', 'n');
    return s;

error:
	printf("Error at %s:%d\n", __FILE__, __LINE__);
	exit(1);
}

#endif
