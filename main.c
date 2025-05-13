#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "run/main.h"

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
  int syssh;                                                                                   
  char *rootworkdir;                                                                         
  int setemptyline;
  char *lastline;  
  char *linebuf;
  char *line;
  char *cwd; 

  FILE *srcfile;                                                                       
} maincontext_t;

void maingetline(maincontext_t *ctxt) 
{
    ctxt->linebuf[0] = 0;

    int displaynumber = 1;
    while loop {
	    char *prtline = 0; size_t prtlinen = 0; ssize_t r;
	    r = getline(&prtline, &prtlinen, stdin);
    	throwngerrno(r);
     	if (strlen(ctxt->linebuf) + strlen(prtline) < NBUF) {
    		strcat(ctxt->linebuf + strlen(ctxt->linebuf), prtline);
    	} else {
    		printf("Buffer overflow.\n");
    		exit(1);
    	}
	
       free(prtline);
       if (strlen(prtline) < 2 
       || (prtline[strlen(prtline) - 2] != '\\'))
  	       break;
           printf("%d ", ++displaynumber);
       }
    
    printf("\n");
}


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
	    escapecstr(ctxt->lastline, linebuf_tn));
	fprintf(ctxt->srcfile, "int syssh = %d;\n", ctxt->syssh);
	fprintf(ctxt->srcfile, "char *rootworkdir = \"%s\";", ctxt->rootworkdir);
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
}

void mainfixinputline(maincontext_t *ctxt)
{
	for (unsigned long i = 0; i < strlen(ctxt->line); ++i) {
		if ((ctxt->line[i] == '\n' || ctxt->line[i] == (char)10) && ctxt->line[i-1] != '\\')
		    ctxt->line[i] = ' ';
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
  
  printf("[press enter] ");

  ctxt->syssh = 0;
  
  ctxt->rootworkdir = argv[1];

  if (ctxt->rootworkdir[strlen(ctxt->rootworkdir) - 1] == '/') {
  	ctxt->rootworkdir[strlen(ctxt->rootworkdir) - 1] = 0;
  }
  
  if (argc < 2) { printf("%s: %s %s%s\n", "Usage", argv[0], "<workdir>", ""); return 1; }

  ctxt->lastline = mallocaddlinebuf;
  ctxt->cwd = mallocaddlinebuf;
  ctxt->setemptyline = 0;
  ctxt->linebuf = mallocaddlinebuf;

  while loop {
    loadcwd(ctxt->rootworkdir);
    getcwd(ctxt->cwd, linebuf_tn);
    
    // printf("%s $ ", cwd); if (syssh) printf("$ ");

    //ctxt->setemptyline = 0;

    if (!ctxt->setemptyline)
    {
    	maingetline(ctxt);
    }
    else {
    	ctxt->linebuf[0] = '\n';
    	ctxt->linebuf[1] = 0;
    	ctxt->setemptyline = 0;
    }
    ctxt->line = ctxt->linebuf;

    in(ctxt->line, fputsclose, fopen(ctxtmwf("log.txt"), "a"));

    if (!ctxt->syssh && 0 == strncmp(ctxt->line, "# exit", 6)) {
    	exit(0);
    }

    mainfixinputline(ctxt);

    mainprintsubmainbegin(ctxt);
	maincdcase(ctxt);
    mainprintsubmainend(ctxt);    

    char quiet[] = " 2> /dev/null > /dev/null";

	// TODO write back to ? : && || syntax
	(sh, "rm -f %s", ctxtmwf("a.out"), endsh);
	if (sh, "gcc %s -o%s", ctxtmwf("main.c"), ctxtmwf("a.out"), endsh) {
		if (strncmp(ctxt->linebuf, " ", 2)) { ctxt->setemptyline = 1; } else {
		    printf(s, "A1");ln;breakpt;
			if (sh, "stat %s %s", mf("%s%s", ctxt->rootworkdir, ".err"), quiet, endsh)
			{
				printf(s, "A2");ln;breakpt;
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
    	(sh, ctxtmwf("a.out"), endsh),
    	(sh, "rm -r %s",    mf("%s%s", ctxt->rootworkdir, ".bak"), 
    	                  /*mf("%s%s", ctxt->rootworkdir, ".bak.bak"),*/ endsh),
    	(sh, "mv %s %s",    mf("%s%s", ctxt->rootworkdir, ".tmp.bak"),
    	                    mf("%s%s", ctxt->rootworkdir, ".bak"), endsh),
	    (sh, "cp -r %s %s", mf("%s%s", ctxt->rootworkdir, ""),
	                        mf("%s%s", ctxt->rootworkdir, ".tmp.bak"), endsh);
	  //(sh, "mv %s %s%s",  mf("%s%s", ctxt->rootworkdir, ".bak.bak"),
	  //                    mf("%s%s", ctxt->rootworkdir, ".bak"), "" , endsh);
	}
	
	strcpy(ctxt->lastline, ctxt->linebuf);
  } 
}
