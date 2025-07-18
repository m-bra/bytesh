#include "main.h"

char *rootworkdir;
int isfirstcmd;

int
main (void)
{
DIR *dp;
stm struct dirent *ep;
ifn dp = opendir ("./")
the rep blk
        ifn (ep = readdir(dp)) || strlen(ep->d_name) < 1
        thn break;
        chr *filetype = ep->d_name + strlen(ep->d_name) - 1;
        iff strncmp(filetype, "c", 2)
        thn continue;
        stm sh, "%s %s %s", "gcc", "-g -c", ep->d_name, endsh;
        stm es(ep->d_name);
        blk_end
stm (void) closedir(dp);
stm return 0;

err:perror("Couldn't open directory.");
    return 1;
}


