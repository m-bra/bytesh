#include "main.h"

#include <stdarg.h>

/* stdio.h */ /* { */

int vprintf(const char *restrict format, va_list ap);
int vfprintf(struct FILE *restrict stream,
            const char *restrict format, va_list ap);
int vsprintf(char *restrict str,
            const char *restrict format, va_list ap);
int vsnprintf(
            char *str, size_t size,
            const char *restrict format, va_list ap);

/* } */


malloclist_t malloclistval;
malloclist_t *malloclist = &malloclistval;

void es_(char *name, char *sz)
{
    char *pre = mf("(%s) = ", name);
    char prespace[strlen(pre)];
	memset(prespace, ' ', strlen(pre));
    
	printf("%s\"", pre);
	while (*sz) {
	iff *sz == '\n'
	thn printf("\\n\"\n%s\"", prespace);
	els printf("%c", *sz);
		fflush(getstdout());
		++sz;
	}
	printf("\"\n");
	fflush(getstdout());
}

char *mlinebufprintf_(malloclist_t *malloclist, char *fmt, ...) 
{
	va_list args;
	va_start(args, fmt);
	vsnprintf(mallocaddlinebuf, linebuf_tn, fmt, args);
	va_end(args);
	return lastmalloc;
}

int sh_(int ignored, char *fmt, ...) 
{
  va_list args;
  va_start(args, fmt);
  linebuf_t buf;

  vsnprintf(buf, sizeof(linebuf_t), fmt, args);

  va_end(args);

  int fd[2];
  pid_t fr = fork(); 
  if (!fr) 
  {
    execl("/bin/sh", "sh", "-c", buf, (char *) NULL);	
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

int shfd_(int ignored, char *fmt, ...) 
{
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
    va_list args;
    va_start(args, fmt);
    linebuf_t buf;

    vsnprintf(buf, sizeof(linebuf_t), fmt, args);

    va_end(args);

    FILE *f = popen(buf, "r");
    return f;
}
