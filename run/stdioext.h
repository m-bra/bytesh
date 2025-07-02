#ifndef RUN_STDIOEXT_H_INCLUDED
#define RUN_STDIOEXT_H_INCLUDED

#include <errno.h>

#include "main.h"

#define ln ;printf("\n");

#define fgetallsclose fgetsclose
#define fgetscloseh printf("%s", "fgetsclose(char *s, int n, FILE *f)")ln;
char *fgetsclose(char *sz, int n, FILE *f)
{
	int const NNULLCH = 1;
	char *result = sz;
	while ((n > NNULLCH) && fgets(sz, n, f))
	{
		n-= strlen(sz);
		sz+= strlen(sz);
	}
	fclose(f);
	return result;
}

char *fgetm(malloclist_t *malloclist, int n, FILE *f)
{
	mallocadd(n);
	char *r = fgets(lastmalloc, n, f);
	return r ? lastmalloc : 0;	
}
#define fgetm(n, f) fgetm(malloclist, n, f)

char *fgetmclose(int n, FILE *f)
{
	char *result = fgetm(n, f);
	fclose(f);
	return result;
}

#define fputscloseh printf("%s", "fputsclose(char *s, FILE *f)")ln;
void fputsclose(char *sz, FILE *f)
{
	fputs(sz, f);
	fclose(f);
}

#define LOADBUFN (16 * 1024)
char *loads(char *filename)
{
	return fgetsclose(malloc(LOADBUFN), LOADBUFN, fopen(filename, "r"));
}


#endif
