#ifndef RUN_MAIN_H_INCLUDED
#define RUN_MAIN_H_INCLUDED


#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>

#include "mainsys.h"
#include "stdlibext.h"
#include "stringext.h"
#include "stringutil.h"
#include "stdioext.h"
#include "unistdext.h"
#include "mathext.h"

txt

fnc void sighandle(int signum)
def
	switch (signum)
	{
	case SIGSEGV:
		printf("SIGSEGV%c", *"\n");
		exit(1);
		break;
	case SIGILL:
		printf("SIGILL%c", *"\n");
		exit(1);
		break;
	case SIGFPE:
		printf("SIGFPE%c", *"\n");
		exit(1);
		break;
	default:
		printf("Signal %d%c", signum, *"\n");
		exit(1);
		break;
	}

#define GLOBAL_INDENT ""
//#define GLOBAL_INDENT "                           "

#define loctag

#define MAIN_BEGIN \
    \
    main_init(argc, argv); \

fnc void main_init(int argc, char **argv)
def
    signal(SIGSEGV, sighandle);
cen signal(SIGILL, sighandle);
cen signal(SIGFPE, sighandle);
cen

	void main_begin(int argc, char **argv);
	main_begin(argc, argv);

	return;
	
err:
	printf("Error at %s:%d%c", __FILE__, __LINE__, *"\n");
	return;
    
#define MAIN_END ;statusprint(rootworkdir);

dat

    int isfirstcmd;
    extern 
    char *rootworkdir;

txt

fnc void cmdlogat(int i, linebuf_t *buf)
def

	FILE *f = fopen(ROOTC("/run/log.txt"), "r");
cen int linen = -1;

rep blk
stm linen+= 1;
ifn fgets((char *) buf, linebuf_tn, f)
thn break;
iff linen == i
thn break;
end_blk
	
stm fclose(f);
stm return;

err:	
stm perror(mf("%s:%d\n", __FILE__, __LINE__));
stm return;

FUNCTION int cmdlogn()

def

stm linebuf_t val;
stm linebuf_t *buf = &val;
	
stm FILE *f = fopen(ROOTC("run/log.txt"), "r");
cen
	
stm int linen = -1;
rep blk
stm linen+= 1;
iff !fgets(asstr buf, linebuf_tn, f)
thn break;
end_blk
	
stm fclose(f);
stm return linen;

err:
stm perror(mf("%s:%d", __FILE__, __LINE__));
stm return 0;

SECTION DATA

#include ".//userinterface.h"

#define PROMPT "0x%04X.priv.c %s $ "

stm int cmdlogn();

SECTION TEXT

FUNCTION void statusprint(char *rootworkdir)

def
chr cwd[NBUF]; getcwd(cwd, NBUF);

chr quiet[] = " 2> /dev/null > /dev/null";

int gitupdaterequired(char *);
    
chr *status = mf(
    	mf("%s%s", "\n%s[%s]\n%s\n", PROMPT), 
    	GLOBAL_INDENT, cwd, 
    	GLOBAL_INDENT, 
    	cmdlogn(),
    	//(gitupdaterequired(ROOTC(".")) ? "(.../bytesh/) " : ""),
    	mf("%s%s", 
    		!(sh, "stat %s%s %s", rootworkdir, ".err", quiet, endsh) ? " (ERRFIX) " : "",
			gitupdaterequired("/storage/self/primary/prj/bytesh/") ? ("!(bytesh/)") : ""
    	)
    );
    printf("%s", status);
    fflush(stdout);
    fputsclose(status, fopen(mf("%s/%s", rootworkdir, "status.txt"), "w"));

dat

#include "cnslutil.h"
#include "misc.h"

txt

fnc void main_begin(int argc, char **argv)
def
	if (isfirstcmd && argc > 1 && 0 == strncmp(argv[1], "setupvnc", 8)) {\
	    printf("%s", "setup vnc? [n] ");\
	    if (!strncmp(mgetescline("%d "), "y", 1)) {\
	      printf("setup vnc...");ln; \
	      vncserver; \
	      sh, "sleep 5", endsh; \
	      firefox;\
	    }\
	}

fnc void unused_main()
blk blk_end

#include "projects.h"
#include "tmp.h"


#endif
