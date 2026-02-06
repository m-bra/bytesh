#include "main.h"

#include <sys/types.h>
#include <dirent.h>
#include "../cflags.h"

#undef precompile
int precompile (void)
blk
stm printf("(tag)\n");
DIR *dp;
stm struct dirent *ep;
iff !(dp = opendir (ROOTC("/run/")))
the rep blk
        iff !(ep = readdir(dp)) 
        thn break;
        iff strlen (ep->d_name) < 2
	thn continue;
        chr *filetype = ep->d_name + strlen(ep->d_name) - 2;
        iff strncmp(filetype, cmpentire(".c")) 
         || !strncmp(ep->d_name, cmpentire ("main.c"))
        thn continue;
	stm ep->d_name[strlen(ep->d_name) - 2] = '\0';
	int defstrchrnul = 1; // since we just assume to not be prooted here
	chr *cmd = mf("gcc %s %s%s%s%s%s%s%s%s",
		CFLAGS(defstrchrnul),
	        " -c ", ROOTC("/run/"), ep->d_name, ".c",
		" -o ", ROOTC("/run/"), ep->d_name, ".o");
	stm printf("%s\n", cmd);
        stm sh, cmd, endsh;
        blk_end
stm (void) closedir(dp);
stm return 0;

err:perror("Couldn't open directory.");
    return 1;
end


