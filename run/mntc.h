#define mntch edit, ROOTC("/run/mntc.h"), endsh
#define mntchadd hadd("mntc")
#define mntchaddfn(ident) haddfn("mntc", ident)
#define mntchadddef(ident) hadditem("mntc", ident, 1)

int gitupdaterequired(char *dir) {
	sh, "cd %s", dir, endsh;

	sh, "git status > %s", ROOTC("/run/gitstatus.txt"), endsh;
	FILE *f = fopen(ROOTC("/run/gitstatus.txt"), "r");\

	char *lastline = 0;
	rep {
	    char *line = fgetm(linebuf_tn, f); 
	    if (!line) 
	    {
   	    iff !lastline
	    thn break;
	    	es(lastline);
	        char *cmpwith = "nothing to commit, working tree clean";
	    iff 0 == strncmp(lastline, cmpwith, strlen(cmpwith))
	    thn return 0;   
	    	break;
	    }
	    lastline = line;
	}
	rm, ROOTC("/run/gitstatus.txt"), endsh;
	return 1;	
}


