#include "main.h"

#include <sys/types.h>
#include <dirent.h>

#define cmpentire(sz) sz, strlen(sz) + 1

#undef precompile
int precompile (void)
{
DIR *dp;
stm struct dirent *ep;
iff !(dp = opendir (ROOTC("/run/")))
the rep blk
        iff !(ep = readdir(dp)) 
        thn break;
        iff strlen (ep->d_name) < 1
	thn break;
        chr *filetype = ep->d_name + strlen(ep->d_name) - 1;
        iff strncmp(filetype, cmpentire("c")) 
         || !strncmp(ep->d_name, cmpentire ("main.c"))
        thn continue;
	chr *cmd = mf("gcc -Wfatal-errors %s%s%s%s%s%s%s", 
	        " -c ", ROOTC("/run/"), ep->d_name, 
		" -o ", ROOTC("/run/"), ep->d_name, ".o");
	stm printf("%s\n", cmd);
        stm sh, cmd, endsh;
        blk_end
stm (void) closedir(dp);
stm return 0;

err:perror("Couldn't open directory.");
    return 1;
}


