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
#define kib_tn sizeof(kib_t)
#define mallocaddkib mallocadd(sizeof(kib_t))
typedef char linebuf_t[256];
#define linebuf_tn sizeof(linebuf_t)
#define mallocaddlinebuf mallocadd(sizeof(linebuf_t))
typedef char pagebuf_t[sizeof(linebuf_t) * 128];
#define pagebuf_tn sizeof(pagebuf_t)
#define mallocaddpagebuf mallocadd(sizeof(pagebuf_t))
//#call assert(sizeof pagebuf_t == 32 * sizeof kib_t);

#define ROOT "/data/data/com.termux/files/home/prj/bytesh/"
#define ROOTLEN strlen(ROOT)
#define ROOTC(arg) (\
    mallocaddlinebuf,\
    in((char *)lastmalloc, strcpy, ROOT),\
    snprintf((char *)lastmalloc, sizeof(linebuf_t), "%s%s%s", ROOT, "/", arg),\
    (char *)lastmalloc\
)

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
