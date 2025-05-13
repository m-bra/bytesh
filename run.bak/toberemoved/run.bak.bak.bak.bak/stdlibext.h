#ifndef STDLIBEXTH_INCLUDED
#define STDLIBEXTH_INCLUDED

#include <unistd.h>
#include <sys/wait.h>

#include "main.h"

#define MALLOCLISTMAXPTRS 2048
typedef struct
{
	void *ptrs[MALLOCLISTMAXPTRS];
	int nptrs;
} malloclist_t;
#define lastmalloc (malloclist->ptrs[malloclist->nptrs - 1])

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

    return lastmalloc;
}
#define mallocadd(size) mallocadd_(malloclist, size)

malloclist_t malloclistval;
malloclist_t *malloclist = &malloclistval;


#define breakpt ; {char c[8]; fgets(c, 8, stdin);};

#define in(a, f, b) f ( a , b )

#define loop (1)

#define throwngerrno(x)                     \
    if (x < 0) {                            \
        printf("Error at ");                \
  	    printf("%s:", __FILE__);            \
  		printf("%d\n", __LINE__);           \
  		printf("%s\n", strerror(errno));    \
  		exit(1);                            \
  	}                                       \
//

#include <stdarg.h>

char *mlinebufprintf_(malloclist_t *malloclist, char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	vsnprintf(mallocaddlinebuf, linebuf_tn, fmt, args);
	va_end(args);
	return lastmalloc;
}
#define mlinebufprintf(...) mlinebufprintf_(malloclist, __VA_ARGS__)
#define malloclinebufprintf mlinebufprintf

int sh_(int ignored, char *fmt, ...) 
{
  va_list args;
  va_start(args, fmt);
  linebuf_t buf;

  vsnprintf(buf, sizeof(linebuf_t), fmt, args);

  va_end(args);

  pid_t fr = fork(); 
  if (!fr) 
  {
    execl("/bin/sh", "sh", "-c", buf, (char *) NULL);	
  }
  else
  {
  	int wstatus;
  	wait(&wstatus);
  	return !WIFEXITED(wstatus) || WEXITSTATUS(wstatus);
  }
  return 1;
}

#define sh sh_ ( 0
#define endsh "" )

#endif
