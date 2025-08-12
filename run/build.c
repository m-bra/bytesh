#include "main.h"

#include <sys/types.h>
#include <dirent.h>

#define cmpentire(sz) sz, strlen(sz) + 1

#undef precompile
int precompile (void)
{
stm printf("lalala\n");
DIR *dp;
stm struct dirent *ep;
ifn dp = opendir (ROOTC("/run/"))
the rep blk
        ifn (ep = readdir(dp)) 
        thn break;
        iff strlen (ep->d_name) < 1
	thn break;
        chr *filetype = ep->d_name + strlen(ep->d_name) - 1;
        iff strncmp(filetype, cmpentire("c")) 
         || !strncmp(ep->d_name, cmpentire ("main.c"))
        thn continue;
        stm es(ep->d_name);
        stm sh, "%s%s%s%s%s%s%s%s", 
	        "gcc ", "-Wfatal-errors -c ", ROOTC("/run/"), ep->d_name, 
		    "-o ", ROOTC("/run/"), ep->d_name, ".o", endsh;                 
        blk_end
stm (void) closedir(dp);
stm return 0;

err:perror("Couldn't open directory.");
    return 1;
}


