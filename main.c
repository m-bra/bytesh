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
			
		fputsclose
		(
		    mlinebufprintf("%s/%s/\n", ctxt->cwd, ctxt->line), 
		    fopen(ctxtmwf("cwd.txt"), "w")
		);
		loadcwd(ctxt->rootworkdir);

		ctxt->line = ctxt->line + strlen(ctxt->line);
	}	

	if (0 == strncmp(ctxt->line, "# cdroot ", 9)) {
		ctxt->line += 9;
		ctxt->line[strlen(ctxt->line) - 1] = 0;
			
		fputsclose
		(
		    mf("%s/\n", ctxt->line), 
		    fopen(ctxtmwf("cwd.txt"), "w")
		);
		loadcwd(ctxt->rootworkdir);

		ctxt->line = ctxt->line + strlen(ctxt->line);
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

int main(int argc, char **argv) {
  maincontext_t *ctxt = mallocadd(sizeof(maincontext_t));

  linebuf_t runopt;

  int defstrchrnul = 0;

  /*
  while loop {
	//printf("prooted? [y] ");
	fflush(stdout);
	//char *answer = mgetescline("");

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
  */

  fflush(stdout);
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

  while loop {
    loadcwd(ctxt->rootworkdir);
    getcwd(ctxt->cwd, linebuf_tn);
    
    // printf("%s $ ", cwd); if (syssh) printf("$ ");

    //ctxt->setemptyline = 0;

    if (!ctxt->setemptyline)
    loctag {
        ctxt->linebuf[0] = 0;

        char page[pagebuf_tn];
        page[0] = 0;
		fgetallsclose(page, pagebuf_tn - 1, fopen(ROOTC("/insert.c"), "r"));

        // add fskipwh here
    iff !strlen(page)
    thn	{    strncat(ctxt->linebuf, mgetescline(mf("%s%%02d ", GLOBAL_INDENT)), pagebuf_tn - 1);ln;}
    els {    strncat(ctxt->linebuf, page,                                       pagebuf_tn - 1);
             fputsclose("", fopen(ROOTC("/insert.c"), "w"));
             printf("<insert.c>\n\n");
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

	// TODO write back to ? : && || syntax
	(sh, "rm -f %s", ctxtmwf("a.out"), endsh);
	if (sh, "gcc %s %s -o%s", defstrchrnul ? "-D DEFSTRCHRNUL" : "", ctxtmwf("main.c"), ctxtmwf("a.out"), endsh) {
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
				printf(s, mf("%s%s %s", ctxt->rootworkdir, ".err", "already exists"));ln;
		}
	} else {
    	(sh, "%s %s %s", runopt, ctxtmwf("a.out"), argc > 2 ? argv[2] : "", endsh);

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
	
	strcpy(ctxt->lastline, ctxt->linebuf);
	ctxt->isfirstcmd = 0;
  } 
}
