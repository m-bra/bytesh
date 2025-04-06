#ifndef STDLIBEXTH_INCLUDED
#define STDLIBEXTH_INCLUDED

#include "main.h"

#define MALLOCLISTMAXPTRS 2048
typedef struct
{
	void *ptrs[MALLOCLISTMAXPTRS];
	int nptrs;
} malloclist_t;
#define lastmalloc (malloclist->ptrs[malloclist->nptrs - 1])

void *mallocadd_(malloclist_t *malloclist, int size)
{
	if (malloclist->nptrs + 1 > MALLOCLISTMAXPTRS)
	{
		printf("Error at %s:%d\n", __FILE__, __LINE__);
		exit(1);
	}

    malloclist->ptrs[malloclist->nptrs] = malloc(size);
    malloclist->nptrs += 1;
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

#endif
