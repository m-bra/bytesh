#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "run/main.h"

char *rootworkdir;

void loadcwd(char *rootworkdir)
{  
    char path[NBUF]; snprintf(path, NBUF, "%s/cwd.txt", rootworkdir);
//    printf("path = '%s'\n", path);
    char line[NBUF]; fgetsclose(line, NBUF, fopen(path, "r"));
    line[strlen(line) - 1] = 0;
//    printf("line = '%s'\n", line);
    int r = chdir(line);
    if (r < 0) {
        printf("cd: error\n");
        fputsclose("/data/data/com.termux/files/home/prj/bytesh/", fopen(path, "w"));
    }
}

typedef struct {  
  int isfirstcmd;                     
  int syssh;                                                                                   
  char *rootworkdir;                                                                         
  int setemptyline;
  char *lastline; int lastlinen;
  char *linebuf;
  char *line;
  char *cwd; 

  FILE *srcfile;                                                                       
} maincontext_t;

char *ctxtmwf(malloclist_t *malloclist, maincontext_t *ctxt, char *path)
{
	return mlinebufprintf("%s/%s", ctxt->rootworkdir, path);
}
#define ctxtmwf(path) ctxtmwf(malloclist, ctxt, path)
#define ctxtmrootworkdirfile ctxtmwf

void mainprintsubmainbegin(maincontext_t *ctxt)
{
    ctxt->srcfile = fopen(ctxtmwf("main.c"), "w");
    	fprintf(ctxt->srcfile, "#include \"main.h\"\n");
	fprintf(ctxt->srcfile, "\n");
	fprintf(ctxt->srcfile, "char *lastcmd = \"%s\";\n", 
	    escapecstr(ctxt->lastline, ctxt->lastlinen));
	fprintf(ctxt->srcfile, "int syssh = %d;\n", ctxt->syssh);
	fprintf(ctxt->srcfile, "char *rootworkdir = \"%s\";", ctxt->rootworkdir);
	fprintf(ctxt->srcfile, "int isfirstcmd = %d;", ctxt->isfirstcmd);
	fprintf(ctxt->srcfile, "\n");
	fprintf(ctxt->srcfile, "int main(int argc, char **argv) {\n");
	fprintf(ctxt->srcfile,     "MAIN_BEGIN\n");	
}

void maincdcase(maincontext_t *ctxt)
{
	if (0 == strncmp(ctxt->line, "# cd ", 5)) {
		ctxt->line += 5;
		ctxt->line[strlen(ctxt->line) - 1] = 0;

		int isroot = strlen(ctxt->line) && ctxt->line[0] == '/';

       	fputsclose
		(
		    mf("%s/%s/\n", isroot ? "" : ctxt->cwd, ctxt->line), 
		    fopen(ctxtmwf("cwd.txt"), "w")
		);
		loadcwd(ctxt->rootworkdir);

		// ctxt->line = ctxt->line + strlen(ctxt->line);
		ctxt->line = ctxt->linebuf;
		ctxt->line[0] = 0;   			
	}	
}

void mainremoveunescnl(char *line)
{
	for (unsigned long i = 1; i < strlen(line); ++i) {
		if ((line[i] == '\n' || line[i] == (char)10))
			if ((line[i-1] != '\\'))
		    	line[i] = ' ';
	}    	
}

void mainprintsubmainend(maincontext_t *ctxt)
{
	fprintf(ctxt->srcfile, "%s", ctxt->line);		
	fprintf(ctxt->srcfile,     "\nMAIN_END");
	fprintf(ctxt->srcfile, "}");	
	fclose(ctxt->srcfile);
}

loctag
int submain(int argc, char **argv) {
  maincontext_t *ctxt = mallocadd(sizeof(maincontext_t));

  ed(argc);
  if (2 < argc)
  es(argv[2] ? argv[2] : "(null)");

  linebuf_t runopt;

  int defstrchrnul = 0;

  if (!argv[2])
  while loop {
	printf("prooted? [y] ");
	fflush(stdout);
	char *answer = mgetline("");

  	if (!strncmp(answer, "y", 1)) {
  	  defstrchrnul = 0;
      break;
  	}
  	if (!strncmp(answer, "n", 1)) {
      defstrchrnul = 1;
      break;
  	}
  	defstrchrnul = 0;
  	break;
  }
  

  fflush(stdout);
  if (!argv[2])
  	printf("[press enter] ");
  fflush(stdout);

  ctxt->isfirstcmd = 1;
  ctxt->syssh = 0;
  
  ctxt->rootworkdir = argv[1];
  rootworkdir = ctxt->rootworkdir;

  if (ctxt->rootworkdir[strlen(ctxt->rootworkdir) - 1] == '/') {
  	ctxt->rootworkdir[strlen(ctxt->rootworkdir) - 1] = 0;
  }
  
  if (argc < 2) { printf("%s: %s %s%s\n", "Usage", argv[0], "<workdir>", ""); return 1; }

  ctxt->lastline = mallocadd(10 * linebuf_tn);
  ctxt->lastlinen = 110 * linebuf_tn;
  ctxt->cwd = mallocaddlinebuf;
  ctxt->setemptyline = 0;
  ctxt->linebuf = mallocaddpagebuf;

  int nextbackup = 10;

  rep {
    loadcwd(ctxt->rootworkdir);
    getcwd(ctxt->cwd, linebuf_tn);
    
    // printf("%s $ ", cwd); if (syssh) printf("$ ");

    //ctxt->setemptyline = 0;

    if (!ctxt->setemptyline)
    {
        ctxt->linebuf[0] = 0;

        char page[pagebuf_tn]; page[0] = 0;
    iff argv[2]
    thn strcpy(page, argv[2]);
	els fgetallsclose(page, pagebuf_tn - 1, fopen(ROOTC("/insert.c"), "r"));

    stm char *status = mallocaddlinebuf;
    stm FILE *statusfile = fopen(ROOTC("/run/status.txt"), "r");
    rep ifn fgets(status, linebuf_tn, statusfile)
        thn break;
    stm fclose(statusfile);
    stm int skipstatuslen = strlen(status) - 5;
    stm char skipstatus[skipstatuslen + 1];
    for range(0, skipstatuslen)
    stm skipstatus[i] = ' ';
    stm skipstatus[skipstatuslen] = 0;

        // add fskipwh here
    iff !strlen(page)
    thn	{    strncat(ctxt->linebuf, mgetline(mf("%s%%02d $ ", skipstatus)), pagebuf_tn - 1);ln;}
    els {    strncat(ctxt->linebuf, page,                                       pagebuf_tn - 1);
             fputsclose("", fopen(ROOTC("/insert.c"), "w"));
             if (!argv[2]) printf("<insert.c>\n\n");
        }
    }
    else {
    	ctxt->linebuf[0] = '\n';
    	ctxt->linebuf[1] = 0;
    	ctxt->setemptyline = 0;
    }
    ctxt->line = ctxt->linebuf;

    if (0 == strncmp(ctxt->line, "# exit", 6)) 
    {
    	exit(0);
    }

    if (0 == strncmp(ctxt->line, "# restart", 9)) 
    {
    	exit(5);
    }

	char *cmdprefix = "# runopt ";
    if (0 == strncmp(ctxt->line, cmdprefix, strlen(cmdprefix)))
    {
    	ctxt->line += strlen(cmdprefix);	
   		ctxt->line[strlen(ctxt->line) - 1] = 0;
   			
		strncpy(runopt, ctxt->line, linebuf_tn - 1);
		runopt[linebuf_tn - 1] = 0;
   
   		ctxt->line = ctxt->line + strlen(ctxt->line);
    }

    in(ctxt->line, fputsclose, fopen(ctxtmwf("log.txt"), "a"));

    mainremoveunescnl(ctxt->line);


    if (0 == strncmp(ctxt->line, "# 0x", 4)) {
        printf("unimplemented");ln;

    } if (0) {
		int i = strtol(ctxt->line + 4, NULL, 16);

    	ctxt->linebuf[0] = 0;
    	ctxt->line = ctxt->linebuf;

		while loop {
			linebuf_t cmd;
			cmdlogat(i, &cmd);
	        int linebuflen = strlen(ctxt->linebuf); 
	        if (linebuflen + strlen(cmd) + 4 < pagebuf_tn) {
				
				strncpy(&ctxt->linebuf[linebuflen], cmd, strlen(cmd) + 1);
			} else {
				printf("Error at %s:%d", __FILE__, __LINE__);ln;
			}
			
			if (!strncmp(&cmd[strlen(cmd) - 2], "\\\n", 2)) {
				++i;
			} else {
				break;
			}
		}
    }

    mainprintsubmainbegin(ctxt);
	maincdcase(ctxt);
    mainprintsubmainend(ctxt);    

    char quiet[] = " 2> /dev/null > /dev/null";

    sh, "mv %s %s %s", 
        mf("-f %s/%s", ctxt->rootworkdir, "a.out"), 
        mf("%s/%s", ctxt->rootworkdir, "b.out"), 
        QUIET, endsh;

    char *defstrchrnulflag = defstrchrnul ? "-D DEFSTRCHRNUL" : "";
	char *flags = mf("%s %s", "-g", defstrchrnulflag);

	(sh, "rm -f %s", ctxtmwf("a.out"), endsh);

	if (sh, "gcc %s %s -o%s", flags, ctxtmwf("main.c"), ctxtmwf("a.out"), endsh) {
		if (strncmp(ctxt->linebuf, " ", 2)) { ctxt->setemptyline = 1; } else {
			if (sh, "stat %s %s", mf("%s%s", ctxt->rootworkdir, ".err"), quiet, endsh)
			{
				if (sh, "mv %s %s", 
				     ctxt->rootworkdir, mf("%s%s", ctxt->rootworkdir, ".err", endsh)
				) { printf("Error at %s:%d\n", __FILE__, __LINE__); } else {
                if (sh, "cp -r %s %s",
                     mf("%s%s", ctxt->rootworkdir, ".bak"), ctxt->rootworkdir, endsh
                ) { printf("Error at %s:%d\n", __FILE__, __LINE__); }}
			}
			else
				printf("%s", mf("%s%s %s", ctxt->rootworkdir, ".err", "already exists"));ln;
		}
	} else 
	{
		mv, ctxtmwf("a.out"), "/data/data/com.termux/files/home/a.out", endsh;
		chmodx, "/data/data/com.termux/files/home/a.out", endsh;
	    sh, "%s %s", runopt, "/data/data/com.termux/files/home/a.out", endsh;

    ign blk
		stm FILE *tee = fopen(ROOTC(mf("/run/log/0x%X.txt", cmdlogn())), "w");
		cen char buf[pagebuf_tn];
	    stm int fd = (shfd, "%s %s", runopt, ctxtmwf("a.out"), endsh);
		rep blk
		s   int wstatus;
	    s   stm waitpid(-1, &wstatus, WNOHANG);
	    s   int werrno = errno;
	    s   iff werrno && werrno != ECHILD
	    s   the 
		s   int n = read(fd, buf, pagebuf_tn);
		s   iff n == -1
		s   the
		s   iff n > 0
		s   thn {fwrite(buf, 1, n, stdout); fwrite(buf, 1, n, tee);}
        s
		s   iff WIFEXITED(wstatus) || werrno == ECHILD
	    s   thn break; 
		s   blk_end
		stm fclose(tee);
		stm fflush(stdout);
        blk_end

    	if (!nextbackup--)
    	{
    		nextbackup = 10,
            (sh, "rm -r %s",    mf("%s%s", ctxt->rootworkdir, ".bak"), 
    		                  /*mf("%s%s", ctxt->rootworkdir, ".bak.bak"),*/ endsh),
    		(sh, "mv %s %s",    mf("%s%s", ctxt->rootworkdir, ".tmp.bak"),
    		                    mf("%s%s", ctxt->rootworkdir, ".bak"), endsh),
	        (sh, "cp -r %s %s", mf("%s%s", ctxt->rootworkdir, ""),
	                            mf("%s%s", ctxt->rootworkdir, ".tmp.bak"), endsh);
	      //(sh, "mv %s %s%s",  mf("%s%s", ctxt->rootworkdir, ".bak.bak"),
	      //                    mf("%s%s", ctxt->rootworkdir, ".bak"), "" , endsh);
		
    	}
	}

iff argv[2]
thn break;
	
	strcpy(ctxt->lastline, ctxt->linebuf);
	ctxt->isfirstcmd = 0;
  }
  return 0; 

err:
  perror(mf("%s:%d", __FILE__, __LINE__));
  return 1;
}

SECTION TEXT

FUNCTION int main(int iargc, char **iargv) 

def
stm char *cmd = NULL;

iff 1 < iargc
 && !strncmp(iargv[1], "-c", 3)
thn blk
    ifn 2 < iargc
    the cmd = iargv[2];     
end_blk

iff cmd	
thn es(cmd);
els ed((int) (size_t) cmd);

stm char *argv[3] = {"bytesh", ROOTC("/run/"), cmd};
stm submain(3, argv);
stm return 0;

err:
stm printf("Usage: %s [-c <command>]\n", 0 < iargc ? iargv[0] : "bytesh");
stm return 1;

SECTION DATA
