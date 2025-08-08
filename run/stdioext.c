
struct SYSFILE;

struct SYSFILE *stdoutmacro();
struct SYSFILE *stdinmacro();
struct SYSFILE *stderrmacro();
int eofmacro();

struct SYSFILE *getstdout()
{
	return stdoutmacro();
}

struct SYSFILE *getstdin()
{
	return stdinmacro();
}

struct SYSFILE *getstderr()
{
	return stderrmacro();
}

int eof()
{
	return eofmacro();
}

#include <stdio.h>


#define NOSTDIOH
#include "main.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>


struct SYSFILE *stdoutmacro()
{
	return (struct SYSFILE *) stdout;
}

struct SYSFILE *stdinmacro()
{
	return (struct SYSFILE *) stdin;
}

struct SYSFILE *stderrmacro()
{
	return (struct SYSFILE *) stderr;
}

int eofmacro()
{
	return EOF;
}

char *fgetsclose(char *sz, int n, FILE *f);

char *fgetm_(malloclist_t *malloclist, int n, FILE *f);

char *fgetmclose_(malloclist_t *malloclist, int n, FILE *f);

char *fgetallmclose_(malloclist_t *malloclist, int n, FILE *f);

int readm_(malloclist_t *malloclist, int fd, size_t size);

void fputsclose(char *sz, FILE *f);

char *loads(char *filename);


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

char *fgetm_(malloclist_t *malloclist, int n, FILE *f)
{
	mallocadd(n);
	char *r = fgets(lastmalloc, n, f);
	return r ? lastmalloc : 0;	
}

char *fgetmclose_(malloclist_t *malloclist, int n, FILE *f)
{
	char *result = fgetm(n, f);
	fclose(f);
	return result;
}

char *fgetallmclose_(malloclist_t *malloclist, int n, FILE *f)
{
	mallocadd(n);
	return fgetallsclose(lastmalloc, n, f);
}

int readm_(malloclist_t *malloclist, int fd, size_t size)
{
	mallocadd(size);
	return read(fd, lastmalloc, size);
}

void fputsclose(char *sz, FILE *f)
{
	fputs(sz, f);
	fclose(f);
}

char *loads(char *filename)
{
	return fgetsclose(malloc(LOADBUFN), LOADBUFN, fopen(filename, "r"));
}
