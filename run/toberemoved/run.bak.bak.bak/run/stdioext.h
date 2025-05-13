#ifndef RUN_STDIOEXT_H_INCLUDED
#define RUN_STDIOEXT_H_INCLUDED

#include "main.h"

#define ln ;printf("\n");

#define fgetscloseh printf(s, "fgetsclose(char *s, int n, FILE *f)")ln;
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

#define fputscloseh printf(s, "fputsclose(char *s, FILE *f)")ln;
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
