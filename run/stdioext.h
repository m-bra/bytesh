 #ifndef RUN_STDIOEXT_H_INCLUDED
#define RUN_STDIOEXT_H_INCLUDED

#include "main.h"

#define ln ;printf("\n");
#define fgetallsclose fgetsclose
#define fgetscloseh printf("%s", "fgetsclose(char *s, int n, FILE *f)")ln;
#define fgetm(n, f) fgetm_(malloclist, n, f)
#define fgetmclose(n, f) fgetmclose_(malloclist, n, f)
#define fgetallmclose(n, f) fgetallmclose_(malloclist, n, f)
#define readm(fd, size) readm_(malloclist, fd, size)
#define fputscloseh printf("%s", "fputsclose(char *s, FILE *f)")ln;
#define LOADBUFN (16 * 1024)


struct SYSFILE *getstdout();
struct SYSFILE *getstdin();
struct SYSFILE *getstderr();
int eof();

#define getstdout() ((FILE *) getstdout())
#define getstdin()  ((FILE *) getstdin())
#define getstderr() ((FILE *) getstderr())

char *fgetsclose(char *sz, int n, FILE *f);

char *fgetm_(malloclist_t *malloclist, int n, FILE *f);

char *fgetmclose_(malloclist_t *malloclist, int n, FILE *f);

char *fgetallmclose_(malloclist_t *malloclist, int n, FILE *f);

int readm_(malloclist_t *malloclist, int fd, size_t size);

void fputsclose(char *sz, FILE *f);

char *loads(char *filename);

#endif
