#include "main.h"

int lastresult = 0;


SECTION TEXT

FUNCTION 

int routine_gitupdaterequired(int counter, char *dir) 
blk
iff counter % 20
thn ret lastresult;

stm cd$$ dir $$;
stm sh$$ "git status > %s", ROOTC("/gitstatus.tmp") $$;
stm FILE *f = fopen(ROOTC("/gitstatus.tmp"), "r");

chr lastline[linebuf_tn];

rep
blk
chr line[linebuf_tn];
chr *r = fgets(line, linebuf_tn, f); 
	
iff !r 
thn blk iff !strlen(lastline)
    thn break;
        chr *cmpwith = "nothing to commit, working tree clean";
    iff 0 == strncmp(lastline, cmpwith, strlen(cmpwith))
    thn ret lastresult = 0;   
    	break;
    end
    
stm strncpy(lastline, line, linebuf_tn);
end

stm sh$$ "rm %s", ROOTC("/gitstatus.tmp") $$;
ret lastresult = 1;	


SECTION DATA
