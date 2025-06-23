#ifndef RUN_MAIN_H_INCLUDED
#define RUN_MAIN_H_INCLUDED


#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <stdio.h>

#include "mainsys.h"
#include "stdlibext.h"
#include "stringext.h"
#include "stringutil.h"
#include "stdioext.h"

void sighandle(int signum)
{
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
}

#define GLOBAL_INDENT ""
//#define GLOBAL_INDENT "                           "

#define loctag

#define MAIN_BEGIN \
    \
    main_init(argc, argv); \

void main_init(int argc, char **argv)
{
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
}
    
#define MAIN_END ;statusprint(rootworkdir);

int isfirstcmd;
extern char *rootworkdir;

//#include "todo.h"

#define PROMPT "0x%04X.priv.c %s $ "

int cmdlogn();

void statusprint(char *rootworkdir)
{
	char cwd[NBUF]; getcwd(cwd, NBUF);

	char quiet[] = " 2> /dev/null > /dev/null";
    
    char *status = mf(
    	mf("%s%s", "\n%s[%s]\n%s", PROMPT), 
    	GLOBAL_INDENT, cwd, 
    	GLOBAL_INDENT, 
    	cmdlogn(),
    	!(sh, "stat %s%s %s", rootworkdir, ".err", quiet, endsh) ? " (ERRFIX)" : ""
    );
    printf("%s", status);
    fputsclose(status, fopen(mf("%s/%s", rootworkdir, "status.txt"), "w"));
}

#include "cnslutil.h"
#include "misc.h"

void main_begin(int argc, char **argv)
{
	if (isfirstcmd && argc > 1 && 0 == strncmp(argv[1], "setupvnc", 8)) {\
	    printf("%s", "setup vnc? [n] ");\
	    if (!strncmp(mgetescline("%d "), "y", 1)) {\
	      printf("setup vnc...");ln; \
	      vncserver; \
	      sh, "sleep 5", endsh; \
	      firefox;\
	    }\
	}
}

#include "projects.h"
#include "tmp.h"


#endif
