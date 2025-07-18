#include "main.h"

int lastresult = 0;


SECTION TEXT

FUNCTION int routine_gitupdaterequired(int counter, char *dir) 

def 
iff counter % 20
thn return lastresult;

    sh, "cd %s", dir, endsh;

	sh, "git status > %s",("/tmp/gitstatus.txt"), endsh;
	FILE *f = fopen(("/tmp/gitstatus.txt"), "r");\

chr lastline[linebuf_tn];

rep
blk
chr line[linebuf_tn];
chr *r = fgets(line, linebuf_tn, f); 
	
iff !r 
thn blk
  	iff !strlen(lastline)
    thn break;
        chr *cmpwith = "nothing to commit, working tree clean";
    iff 0 == strncmp(lastline, cmpwith, strlen(cmpwith))
    thn return lastresult = 0;   
    	break;
    blk_end
    
    strncpy(lastline, line, linebuf_tn);
end_blk

	rm, ("/tmp/gitstatus.txt"), endsh;
	return lastresult = 1;	


SECTION DATA
