#define mtnch edit, ROOTC("/run/mtnc.h"), endsh
#define mtnchadd hadd("mtnc")
#define mtnchaddfn(ident) haddfn("mtnc", ident)
#define mtnchadddef(ident) hadditem("mtnc", ident, 1)


int asdfasdfasfdgitupdaterequired() {
	FILE *f = fopen(ROOTC("/run/gitstatus.txt"), "r");\
	char *lastline = 0;
	rep {
	    char *line = fgetm(linebuf_tn, f); 
	    if (!line) 
	    {
	    iff !lastline
	    thn break;
	        char *cmpwith = "okok";
	    iff 0 == strncmp(lastline, cmpwith, strlen(cmpwith))
	    thn return 0;   
	    	break;
	    }
	    lastline = line;
	}
	return 1;	
}

