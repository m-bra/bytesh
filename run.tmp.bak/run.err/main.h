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
#define MAIN_END ;statusprint(rootworkdir, int argc, char **argv);

extern char *rootworkdir;

//#include "todo.h"

void statusprint(char *rootworkdir, int argc, char **argv)
{
	char cwd[NBUF]; getcwd(cwd, NBUF);

	char quiet[] = " 2> /dev/null > /dev/null";
    
    char *status = mf(
    	"\n[%s]\n%s.c (priv)%s $ ", cwd, argc >= 2 ? argv[1] : "",
    	!(sh, "stat %s%s %s", rootworkdir, ".err", quiet, endsh) ? " (ERRFIX)" : ""
    );
    printf(s, status);
    fputsclose(status, fopen(mf("%s/%s", rootworkdir, "status.txt"), "w"));
}

void test()
{

}

#endif
