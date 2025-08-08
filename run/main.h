#ifndef RUN_MAIN_H_INCLUDED
#define RUN_MAIN_H_INCLUDED

#include <stddef.h> // for size_t

/* stdlib.h */
int system(char const *);
void exit(int status);
void *malloc(size_t size);
void free(void *ptr);

/* string.h */
char *strstr(char const *, char const *);
char *strcpy(char *, char const *);
char *strcat(char *, char const *);
char *strncat(char *, char const *, size_t);
char *strncpy(char *, char const *, size_t);
char *stpncpy(char *, char const *, size_t);
size_t strspn (char const *, char const *);
size_t strcspn(char const *, char const *);
int strcmp(const char *, const char *);
int strncmp(const char *s1, const char *s2, size_t n);
size_t strlen(const char *s);
void *memset(
                    void *s, int c, size_t n);
void *memccpy(
                     void *dest, const void *src,
                     int c, size_t n);
char *strchrnul(const char *s, int c);

/* stdio.h */

#ifndef NOSTDIOH

struct FILE;
typedef struct FILE FILE;
int printf(const char *restrict format, ...);
int fprintf(struct FILE *restrict stream,
            const char *restrict format, ...);
int sprintf(char *restrict str,
            const char *restrict format, ...);
int snprintf(
            char *str, size_t size,
            const char *restrict format, ...);
void perror(const char *sz);

FILE *fopen(const char *restrict path, const char *restrict mode);
int fclose(FILE *stream);
int fflush(FILE */*_Nullable*/ stream);

 
FILE *popen(char const *, char const *);
int pclose(FILE *);


size_t fread(       void *ptr,
                    size_t size, size_t n,
                    FILE *restrict stream);
size_t fwrite(const void *ptr,
                    size_t size, size_t n,
                    FILE *restrict stream);

char *fgets(char *sz, int size, FILE *restrict stream);

int fputc(int c, FILE *stream);
int putc(int c, FILE *stream);
int putchar(int c);

int fputs(const char *restrict s, FILE *restrict stream);
int puts(const char *s);

#endif

/* errno */

#include <errno.h> // its a small header ...

void seterrno(int);
int geterrno();

/* unistd */

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
int dup2(int, int);

//#include <termios.h>

#include "mainsys.h"
#include "stdlibext.h"
#include "stringext.h"
#include "stringutil.h"
#include "stdioext.h"
#include "unistdext.h"
#include "mathext.h"
#include "build.h"

extern int main_interactive;

void main_begin(int argc, char **argv);
void main_init(int argc, char **argv);
void statusprint(char *, int, FILE *, FILE *);
void sighandle(int);

txt

#define GLOBAL_INDENT ""
//#define GLOBAL_INDENT "                           "

#define loctag

SECTION DATA

extern int ORIGINAL_STDOUT_FILENO;

SECTION TEXT

#define MAIN_BEGIN \
	    \
	    main_init(argc, argv); \
    
#define MAIN_END ;\
        //dup2(ORIGINAL_STDOUT_FILENO, STDOUT_FILENO);
	    
	//iff main_interactive 
	//thn {edit, ROOTC("/run/a.out.txt"), endsh;}

SECTION DATA

extern int isfirstcmd;
extern char *rootworkdir;
void cmdlogat(int, linebuf_t *);


#include ".//userinterface.h"

#define PROMPT "0x%04X.priv.c %s $ "

stm int cmdlogn();

SECTION TEXT

SECTION DATA

extern int counter;

SECTION TEXT

dat

#include "cnslutil.h"
#include "misc.h"

txt

FUNCTION inline void unused_main()
blk blk_end

#include "preprocessor.h"
#include "projects.h"
#include "tmp.h"


#endif
