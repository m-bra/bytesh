
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define NOSTDIOH
#include "main.h"

/* -lc */
int dup(int);
char *getcwd(char *, size_t);

int ORIGINAL_STDOUT_FILENO;
int counter = 14;

void main_begin(int argc, char **argv)
{
	if (isfirstcmd && argc > 1 && 0 == strncmp(argv[1], "setupvnc", 8)) {\
	    printf("%s", "setup vnc? [n] ");\
	    if (!strncmp(mgetescline("%d "), "y", 1)) {\
	      printf("setup vnc...\n"); \
	      vncserver; \
	      sh, "sleep 5", endsh; \
	      firefox;\
	    }\
	}
}

SECTION TEXT

FUNCTION int cmdlogn()

def

stm linebuf_t val;
stm linebuf_t *buf = &val;

    errno = 0;
    FILE *f = fopen(ROOTC("run/log.txt"), "r");
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
stm printf("\n");
stm perror(mf("%s:%d", __FILE__, cen_line));
stm return 0;

FUNCTION void main_init(int argc, char **argv)
def
    errno = 0;
    // signal(SIGSEGV, sighandle);
cen // signal(SIGILL, sighandle);
cen // signal(SIGFPE, sighandle);
cen

    // int fd = open(ROOTC("/tmp/byteshpipe.txt"), O_WRONLY | O_TRUNC);
iff argc >= 2
thn ORIGINAL_STDOUT_FILENO = atoi(argv[1]);
els ORIGINAL_STDOUT_FILENO = dup(STDOUT_FILENO);
iff !main_interactive
thn 
    ;// dup2(fd, STDOUT_FILENO);

    void main_begin(int argc, char **argv);
	main_begin(argc, argv);

	return;
	
err:
	printf("Error at %s:%d%c", __FILE__, __LINE__, *"\n");
	return;

FUNCTION void statusprint(char *rootworkdir, int runstatus, FILE *first, FILE *second)

def
chr cwd[NBUF]; getcwd(cwd, NBUF);

chr quiet[] = " 2> /dev/null > /dev/null";

int routine_gitupdaterequired(int, char *);
   
stm FILE *datefile = popen("TZ='Europe/Kyiv' date +%Y-%b-%d\\ %H:%M:%S", "r");
chr szdate[256];
stm fgets(szdate, 254, datefile);
stm szdate[strlen(szdate) - 1] = '\0';
stm pclose (datefile);

//stm FILE *datedatefile = popen(mf("date +%%Y-%%b-%%d\\ %%H:%%M:%%S --date='TZ=+04:00 %s'", szdate), "r");
//chr szdatedate[256];
//stm fgets(szdatedate, 254, datedatefile);
//stm szdatedate[strlen(szdatedate) - 1] = '\0';
//stm pclose (datedatefile);

chr *status = mf(
    	mf("\n%s%s", "%s[0x%02X] ", PROMPT), 
    	GLOBAL_INDENT, runstatus, 
    	
	/* date */
	szdate,
    	cmdlogn(),
    	//(gitupdaterequired(ROOTC(".")) ? "(.../bytesh/) " : ""),
    	mf("%s%s", 
    		(!(sh, "stat %s%s %s", rootworkdir, ".err", quiet, endsh) ? " (ERRFIX)" : ""),
			routine_gitupdaterequired(++counter, "/storage/self/primary/prj/bytesh/") ? (" !(bytesh/)") : "" 
    	)
    );
    fprintf(first,  "%s", status);
    fprintf(second, "%s", status);
    fflush(first);
    fflush(second);

/*
FUNCTION inline void sighandle(int signum)
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

*/

FUNCTION inline void cmdlogat(int i, linebuf_t *buf)
def

    errno = 0;
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
stm perror(mf("%s:%d\n", __FILE__, cen_line));
stm return;

SECTION DATA
