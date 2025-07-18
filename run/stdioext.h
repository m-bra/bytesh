 #ifndef RUN_STDIOEXT_H_INCLUDED
#define RUN_STDIOEXT_H_INCLUDED

#include <errno.h>

#include "main.h"

#define ln ;printf("\n");

#define fgetallsclose fgetsclose
#define fgetscloseh printf("%s", "fgetsclose(char *s, int n, FILE *f)")ln;
char *fgetsclose(char *sz, int n, FILE *f);

char *fgetm_(malloclist_t *malloclist, int n, FILE *f);
#define fgetm(n, f) fgetm_(malloclist, n, f)

char *fgetmclose_(malloclist_t *malloclist, int n, FILE *f);
#define fgetmclose(n, f) fgetmclose_(malloclist, n, f)

char *fgetallmclose_(malloclist_t *malloclist, int n, FILE *f);
#define fgetallmclose(n, f) fgetallmclose_(malloclist, n, f)

int readm_(malloclist_t *malloclist, int fd, size_t size);
#define readm(fd, size) readm_(malloclist, fd, size)

#define fputscloseh printf("%s", "fputsclose(char *s, FILE *f)")ln;
void fputsclose(char *sz, FILE *f);

#define LOADBUFN (16 * 1024)
char *loads(char *filename);


#endif
