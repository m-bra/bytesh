#ifndef RUN_MAIN_H_INCLUDED
#define RUN_MAIN_H_INCLUDED

#include <sys/types.h>
#include <stddef.h> // for size_t

/* stdlib.h */
int system(char const *);
void exit(int status);
void *malloc(size_t size);
void free(void *ptr);

/* string.h */
#ifndef NOSTRINGH
char *strstr(char const *, char const *);
char *strrchr(const char *s, int c); 
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
char *strchrnul(char *s, int c);
char *strchr(char const *s, int c);
void *memcpy(
                    void *dest, const void *src,
                    size_t n);
#endif

/* stdio.h */
#ifndef NOSTDIOH

struct FILE;
typedef struct FILE FILE;
int printf(const char *format, ...);
int fprintf(struct FILE *stream,
            const char *format, ...);
int sprintf(char *str,
            const char *format, ...);
int snprintf(
            char *str, size_t size,
            const char *format, ...);
void perror(const char *sz);

FILE *fopen(const char *path, const char *mode);
int fclose(FILE *stream);
int fflush(FILE */*_Nullable*/ stream);
FILE *fmemopen(
                      void *buf, size_t size, const char *mode);
void rewind(FILE *);
 
FILE *popen(char const *, char const *);
int pclose(FILE *);

/* fileno: Converts FILE pointer to integer file descriptor */
int fileno(FILE *stream);

size_t fread(       void *ptr,
                    size_t size, size_t n,
                    FILE *stream);
size_t fwrite(const void *ptr,
                    size_t size, size_t n,
                    FILE *stream);

char *fgets(char *sz, int size, FILE *stream);

int fputc(int c, FILE *stream);
int putc(int c, FILE *stream);
int putchar(int c);

int fputs(const char *s, FILE *stream);
int puts(const char *s);

#endif

/* errno */

#include <errno.h> // its a small header ...

void seterrno(int);
int geterrno();

/* unistd.h */

#ifndef NOUNISTDH

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
int dup(int oldfd);

ssize_t read(int fd, void *buf, size_t count);

/* fsync: Flushes kernel-level buffers for a file descriptor to disk */
int fsync(int fd);

unsigned int sleep(unsigned int seconds);

char *getcwd(char *buf, size_t size);
pid_t fork();
int execl(const char *path, const char *arg, ...);
int dup2(int oldfd, int newfd);
int chdir(const char *path);
int access(const char *path, int mode);
extern int F_OK_VAR;
#ifndef F_OK
#define F_OK F_OK_VAR
#endif

#endif

//#include <termios.h>

#include "mainsys.h"
#include "stdlibext.h"
#include "stringext.h"
#include "stringutil.h"
#include "stdioext.h"
#include "unistdext.h"
#include "mathext.h"
#include "build.h"
#include "../cflags.h"

extern int main_interactive;

void main_begin(int argc, char **argv);
void main_init(int argc, char **argv);
void statusprint(char *, int, FILE *, FILE *);
void sighandle(int);

txt

#define GLOBAL_INDENT "    "
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

#define PROMPT "%s priv.c:%d%s $ "

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
