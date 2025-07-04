#include "main.h"

#ifndef INCLUDEDMNTCH
#define INCLUDEDMNTCH

#define mntch edit, ROOTC("/run/mntc.h"), endsh
#define mntchadd hadd("mntc")
#define mntchaddfn(ident) haddfn("mntc", ident)
#define mntchadddef(ident) hadditem("mntc", ident, 1)

SECTION TEXT

#define testgit gitupdaterequired("/storage/self/primary/prj/bytesh/")
FUNCTION int gitupdaterequired(char *dir) 

def sh, "cd %s", dir, endsh;

	sh, "git status > %s",("/tmp/gitstatus.txt"), endsh;
	FILE *f = fopen(("/tmp/gitstatus.txt"), "r");\

	char lastline[linebuf_tn];

rep
blk
    char line[linebuf_tn];
    char *r = fgets(line, linebuf_tn, f); 
	es(line);
	
iff !r 
thn blk
  	iff !strlen(lastline)
    thn break;
        char *cmpwith = "nothing to commit, working tree clean";
    iff 0 == strncmp(lastline, cmpwith, strlen(cmpwith))
    thn return 0;   
    	break;
    blk_end
    
    strncpy(lastline, line, linebuf_tn);
blk_end

	rm, ("/tmp/gitstatus.txt"), endsh;
	return 1;	


SECTION DATA

#endif
