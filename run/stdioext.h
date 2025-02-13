#ifndef RUN_STDIOEXT_H_INCLUDED
#define RUN_STDIOEXT_H_INCLUDED

#include "main.h"

#define ln ;printf("\n");


char *fgetsclose(char *s, int n, FILE *f)
{
	char *result = s;
	while ((n > 0) && fgets(s, n, f))
	{
		n-= strlen(s);
		s+= strlen(s);
	}
	fclose(f);
	return result;
}

void fputsclose(char *s, FILE *f)
{
	fputs(s, f);
	fclose(f);
}

#define LOADBUFN (16 * 1024)
char *loads(char *filename)
{
	return fgetsclose(malloc(LOADBUFN), LOADBUFN, fopen(filename, "r"));
}

#endif
