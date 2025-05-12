#ifndef RUN_MAIN_H_INCLUDED
#define RUN_MAIN_H_INCLUDED

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "mainsys.h"
#include "stdlibext.h"
#include "stringext.h"
#include "stringutil.h"
#include "stdioext.h"


#include "cnslutil.h"
#include "misc.h"

#define MAIN_BEGIN
#define MAIN_END ;statusprint(syssh);

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
