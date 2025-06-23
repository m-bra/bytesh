#ifndef STDLIBEXTH_INCLUDED
#define STDLIBEXTH_INCLUDED

#include <unistd.h>
#include <sys/wait.h>

#include "main.h"

#define MALLOCLISTDEBUG if (0)

#ifndef NOEVAL
#define ed(x) printf("%s = %d \n", #x, x);
#define ec(x) printf("%s = %c \n", #x, x);
#define ef(x) printf("%s = %f \n", #x, x);

void es(char *name, char *s)
{
	printf("%s ", name);
	while (*s) {
		printf("%c", *s);
		fflush(stdout);
		++s;
	}
}
#define es(x) es(#x, x)
#endif

#define MALLOCLISTMAXPTRS 2048000
typedef struct
{
	void *ptrs[MALLOCLISTMAXPTRS];
	int nptrs;
} malloclist_t;
#define lastmalloc (malloclist->ptrs[malloclist->nptrs - 1])

#define mdecl \
  malloclist_t malloclistobj;\
  malloclist_t *malloclist = &malloclistobj;

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
#define mallocadd(size) mallocadd_(malloclist, size)

void mfree(malloclist_t *malloclist)
{
	MALLOCLISTDEBUG printf("mfree "); ed(malloclist->nptrs);
	
	for (int i = 0; i < malloclist->nptrs; ++i)
		free(malloclist->ptrs[i]);
	malloclist->nptrs = 0;
}
#define mfree mfree(malloclist)

malloclist_t malloclistval;
malloclist_t *malloclist = &malloclistval;


#define breakpt ; {printf("breakpt at %s:%d", __FILE__, __LINE__);char c[8]; fgets(c, 8, stdin);};

#define in(a, f, b) f ( a , b )

#define looph printf("#define loop (1)\n");
#define loop (1)
#define reph printf("REPeat infinitely\n#define rep while (1)\n");
#define rep while (1)
#define iffh printf("IF and only iF \n#define iff if ( (\n");
#define iff if (   (
#define ifnh printf("IF Not \n#define ifn if ( ! (\n");
#define ifn if ( ! (
#define thnh printf("THeN\n#define thn ) )\n");
#define thn ) )
#define elsh printf("ELSe\n#define els else\n");
#define els else
#define cenh printf("Catch ErrNo (after instr) (singular instr)\n#define cen if (errno != 0) goto err;\n");
#define cen if (errno != 0) goto err;
#define cefh printf("Catch EoF (before instr) (paired with thn/the)\n#define cef if (EOF ==\n");
#define cef if (EOF == (
#define theh printf("THen Err\n#define the thn goto err;\n");
#define the thn goto err;

#define then ) )
#define ift if (   (

#define asstr (char *)
#define asmem (char *)
#define nil void

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
#define mf mlinebufprintf

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
