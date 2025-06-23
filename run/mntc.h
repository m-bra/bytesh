#define mntch edit, ROOTC("/run/mntc.h"), endsh
#define mntchadd hadd("mntc")
#define mntchaddfn(ident) haddfn("mntc", ident)
#define mntchadddef(ident) hadditem("mntc", ident, 1)

int gitupdaterequired(char *dir) {
	sh, "cd %s", dir, endsh;

	sh, "git status > %s",("/tmp/gitstatus.txt"), endsh;
	FILE *f = fopen(("/tmp/gitstatus.txt"), "r");\

	char lastline[linebuf_tn];
	rep {
        char line[linebuf_tn];
	    char *r = fgets(line, linebuf_tn, f); 
		es(line);
	    if (!r) 
	    {
   	    iff !lastline
	    thn break;
	        char *cmpwith = "nothing to commit, working tree clean";
	    iff 0 == strncmp(lastline, cmpwith, strlen(cmpwith))
	    thn return 0;   
	    	break;
	    }
	    strncpy(lastline, line, linebuf_tn);
	}
	rm, ("/tmp/gitstatus.txt"), endsh;
	return 1;	
}


