mistake

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
#define MAIN_END ;statusprint(rootworkdir);

//#include "todo.h"

void statusprint(char *rootworkdir)
{
	char cwd[NBUF]; getcwd(cwd, NBUF);

	char quiet[] = " 2> /dev/null";
    
    char *status = mf(
    	"\n[%s]\n.c (priv)%s $ ", cwd,
    	!(sh, "stat %s%s %s", rootworkdir, ".err", quiet, endsh) ? " (ERRFIX)" : ""
    );
    printf(s, status);
    fputsclose(status, fopen(mf("%s/%s", rootworkdir, "status.txt"), "w"));
}

void test()
{

}

#endif
