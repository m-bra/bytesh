#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>

#define NOSTDIOH
#define NOSTRINGH
#include "main.h"

/* stdio.h */ /* { 

int vprintf(const char *restrict format, va_list ap);
int vfprintf(struct FILE *restrict stream,
            const char *restrict format, va_list ap);
int vsprintf(char *restrict str,
            const char *restrict format, va_list ap);
int vsnprintf(
            char *str, size_t size,
            const char *restrict format, va_list ap);

} */

int cen_line = -1;

malloclist_t malloclistval;
malloclist_t *malloclist = &malloclistval;

char *es_(char *name, char *sz)
{
chr *result = sz;
chr *pre = mf("(%s) = ", name);
chr prespace[strlen(pre)];
stm memset(prespace, ' ', strlen(pre));
    
stm printf("%s\"", pre);
stm while (*sz) 
    blk iff *sz == '\n'
        thn printf("\\n\"\n%s\"", prespace);
        els printf("%c", *sz);
        stm fflush(getstdout());
        stm ++sz;
    blk_end
stm printf("\"\n");
stm fflush(getstdout());
stm return result;
}

char *mlinebufprintf_(malloclist_t *malloclist, char *fmt, ...) 
{
	va_list args;
	va_start(args, fmt);
	vsnprintf(mallocadd(linebuf_tn * 6), linebuf_tn * 6, fmt, args);
	va_end(args);
	return lastmalloc;
}

#define initfromvalist \
    ; \
    va_list args; \
    va_start(args, fmt); \
    vsnprintf(&buf[0], sizeof(linebuf_t) * 6, fmt, args); \
    va_end(args);

int shgeneral(char action, char *fmt, ...)
blk linebuf_t buf[6] initfromvalist;
int shgeneral_frombuf(char, char *);
ret shgeneral_frombuf(action, &buf[0]);
end

#define ᚳ(tag, expr) expr

int shgeneral_frombuf(char action, char *buf)
blk 
int fd[2];
stm pipe(fd);
stm pid_t fr = fork();
iff !fr
thn
blk
stm close(fd[0]);
iff action == ᚳ(redirect, 'r') 
thn dup2(fd[1], STDOUT_FILENO);
stm dup2(STDOUT_FILENO, STDERR_FILENO);
stm close(fd[1]);
stm execl("/bin/sh", "sh", "-c", &buf[0], (char *) NULL);
stm _exit(1);
end
els
blk stm close(fd[1]);
    iff action == ᚳ(wait, 'w') 
    thn blk
        int wstatus;
        stm wait(&wstatus);
        ret BOOLTOSYS(WIFEXITED(wstatus))
        	|| WEXITSTATUS(wstatus);
        end
    iff action == ᚳ(redirect, 'r')
    thn ret fd[0];
    stm printf("Warning: Error at %s:%d\n", 
	       __FILE__, __LINE__);
end
ret 1;

err:perror("Error at stdlibext.c\n");
ret 0;
end

int sh_(int ignored, char *fmt, ...)
blk
chr buf[linebuf_tn * 6] initfromvalist;
ret shgeneral_frombuf(ᚳ(action = wait, 'w'), buf);
end

int disabled2(int ignored, char *fmt, ...) 
{
// === shgeneral(
  linebuf_t buf[6] initfromvalist;
  int fd[2];
  pid_t fr = fork(); 
  if (!fr) 
  {
    execl("/bin/sh", "sh", "-c", &buf[0], (char *) NULL);	
  }
  else
  {
  	  int wstatus;
  	  wait(&wstatus);
      return BOOLTOSYS(WIFEXITED(wstatus)) || WEXITSTATUS(wstatus);
  }
  return 1;
  
err:
  perror(mf("%s:%d", __FILE__, __LINE__));
  return 0;
}

void *mallocadd_(malloclist_t *pmalloclist, int size)
{
	malloclist_t *malloclist = pmalloclist;
	if (pmalloclist->nptrs + 1 > MALLOCLISTMAXPTRS)
	{
		printf("Error at %s:%d\n", __FILE__, __LINE__);
		exit(1);
	}

    pmalloclist->ptrs[pmalloclist->nptrs] = malloc(size);
    pmalloclist->nptrs += 1;

    MALLOCLISTDEBUG ed(malloclist->nptrs);
    MALLOCLISTDEBUG ed(MALLOCLISTMAXPTRS);

    return lastmalloc;
}

void mfree_(malloclist_t *malloclist)
{
	MALLOCLISTDEBUG printf("mfree "); ed(malloclist->nptrs);
	
	for (int i = 0; i < malloclist->nptrs; ++i)
		free(malloclist->ptrs[i]);
	malloclist->nptrs = 0;
}

#define ᚳ(tag, expr) expr

int shfd_(int ignored, char *fmt, ...) 
blk
chr buf[sizeof(linebuf_t)*6] initfromvalist;
int shgeneral_frombuf(chr, chr *); 
return shgeneral(ᚳ(action = redirect, 'r'), buf);
end

int disabled(int ignored, char *fmt, ...)
{
// === shgeneral(fmt, ᚳ(action = redirect, 'r'))
  va_list args;
  va_start(args, fmt);
  linebuf_t buf;

  vsnprintf(buf, sizeof(linebuf_t), fmt, args);

  va_end(args);

  int fd[2];
  pipe(fd);
  pid_t fr = fork(); 
  if (!fr) 
  {
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    execl("/bin/sh", "sh", "-c", buf, (char *) NULL);
    _exit(1);	
  }
  else
  {
    close(fd[1]);
    return fd[0];
  }
  return -1;
}

FILE *psh_(int ignored, char *fmt, ...)
{
    linebuf_t buf[6] initfromvalist;
    FILE *f = popen(buf, "r");
    return f;
}

int shdirectout(char *ignore, char *fmt, ...)
blk int current_stdout_fileno = dup(STDOUT_FILENO);
    stm dup2(ORIGINAL_STDOUT_FILENO, STDOUT_FILENO);
    stm linebuf_t buf[6] initfromvalist;
    int res = shgeneral_frombuf(ᚳ(action = wait, 'w'), buf);
    stm dup2(current_stdout_fileno, STDOUT_FILENO);
    ret res;
err:perror(mf("%s:%d", __FILE__, __LINE__));
    ret 0;
end

#define mmapr(f, s) mmap2(f, s)

nil *mmap2(char const *filename, int *size)
blk struct stat statbuf;
int fd = open(filename, O_RDONLY);
stm fstat(fd, &statbuf); 
iff size
thn *size = (int) statbuf.st_size - 1;
nil *m = mmap(/*addr*/ 0, /*len*/ statbuf.st_size - 1, PROT_READ, MAP_SHARED, fd, /*offset*/ 0);
stm close(fd);
stm return m;
end

nil *mmapw(char const *filename, int *size)
blk struct stat statbuf; 
int fd = open(filename, O_RDWR | O_CREAT, (mode_t)0600);
stm fstat(fd, &statbuf);
iff size
thn *size = (int) statbuf.st_size - 1;
chr *m = mmap(/*addr*/ 0, /*len*/ statbuf.st_size - 1, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
stm close(fd);
stm return m;
end
