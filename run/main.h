#ifndef RUN_MAIN_H_INCLUDED
#define RUN_MAIN_H_INCLUDED

#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "assert.h"

#define MAIN_BEGIN
#define MAIN_END statusprint(syssh);

#define NBUF 512
typedef char kib_t[1024];
typedef char linebuf_t[256];
typedef char pagebuf_t[sizeof(linebuf_t) * 128];
//#call assert(sizeof pagebuf_t == 32 * sizeof kib_t);

#define ROOT "/data/data/com.termux/files/home/prj/bytesh/"
#define ROOTLEN strlen(ROOT)
#define ROOTC(arg) (\
    mallocadd(sizeof(linebuf_t)),\
    strcpy((char *)(lastmalloc), ROOT),\
    snprintf((char *)lastmalloc, sizeof(linebuf_t), "%s%s%s", ROOT, "/", arg),\
    (char *)lastmalloc\
)

#define MALLOCLISTMAXPTRS 2048
typedef struct
{
	void *ptrs[MALLOCLISTMAXPTRS];
	int nptrs;
} malloclist_t;
#define lastmalloc (malloclist->ptrs[malloclist->nptrs - 1])

void mallocadd_(malloclist_t *malloclist, int size)
{
	if (malloclist->nptrs + 1 > MALLOCLISTMAXPTRS)
	{
		printf("Error at %s:%d\n", __FILE__, __LINE__);
		exit(1);
	}

    malloclist->ptrs[malloclist->nptrs] = malloc(size);
    malloclist->nptrs += 1;
}
#define mallocadd(size) mallocadd_(malloclist, size)

malloclist_t malloclistval;
malloclist_t *malloclist = &malloclistval;

#include "stdlibext.h"
#include "stringext.h"
#include "stringutil.h"
#include "stdioext.h"

#include "cnslutil.h"
#include "misc.h"

//#include "todo.h"

void statusprint(int issyssh)
{
    linebuf_t statusbuf = "";
    int sbn = sizeof(statusbuf);
    
	char cwd[NBUF]; getcwd(cwd, NBUF);
    
    {
    	snprintf(statusbuf, sbn, "\n[%s]\n",  cwd);
    	if (issyssh) {
    		snprintf(statusbuf, sbn, "%s.sh (priv) $ ", statusbuf);
    	} else {
    		snprintf(statusbuf, sbn, "%s.c (priv) $ ", statusbuf);
    	}
    }

    printf("%s", statusbuf);
    fputsclose(statusbuf, fopen(ROOTC("/run/status.txt"), "w"));
}

void test()
{

}

#endif
