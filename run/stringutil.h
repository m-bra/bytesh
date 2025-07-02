#ifndef RUN_STRINGUTIL_H_INCLUDED
#define RUN_STRINGUTIL_H_INCLUDED

#include "main.h"

char *escapeccstr(char *sz, int buflen, int c, int r)
{
	if (buflen < (int)strlen(sz) * 2) goto error;

    char *p = sz;
    char *end = p + strlen(p);
    while ((p = strchrnul(p, c)) != end)
    {
    	strnmov(p + 1, p, buflen);
    	p[0] = '\\';
    	p[1] = r;
    	p+= 2;
    	end = p + strlen(p);
    }
	return sz;

error:
	printf("Error at %s:%d\n", __FILE__, __LINE__);
	exit(1);
}

char *escapecstr(char *sz, int buflen)
{
    if (buflen < (int)strlen(sz) * 2 * 2 * 2) goto error;
	sz = escapeccstr(sz, buflen, '\\', '\\');
	sz = escapeccstr(sz, buflen, '\"', '\"');
	sz = escapeccstr(sz, buflen, '\n', 'n');
    return sz;

error:
	printf("Error at %s:%d\n", __FILE__, __LINE__);
	exit(1);
}

#endif
