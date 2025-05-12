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
} maincontext_t;

char *ctxtmwf(malloclist_t *malloclist, maincontext_t *ctxt, char *path)
{
	return mlinebufprintf("%s/%s", ctxt->rootworkdir, path);
}
#define ctxtmwf(path) ctxtmwf(malloclist, &ctxt, path)
#define ctxtmrootworkdirfile ctxtmwf

int main(int argc, char **argv) {
  maincontext_t ctxt;
  
  printf("[press enter]");

  ctxt.syssh = 0;
  
  ctxt.rootworkdir = argv[1];

  if (ctxt.rootworkdir[strlen(ctxt.rootworkdir) - 1] == '/') {
  	ctxt.rootworkdir[strlen(ctxt.rootworkdir) - 1] = 0;
  }
  
  if (argc < 2) { printf("%s: %s %s%s\n", "Usage", argv[0], "<workdir>", ""); return 1; }

  ctxt.lastline = mallocaddlinebuf;
  ctxt.setemptyline = 1;

  while ( 1 ) {
    loadcwd(ctxt.rootworkdir);
    char cwd[NBUF]; getcwd(cwd, NBUF);
    
    // printf("%s $ ", cwd); if (syssh) printf("$ ");

    ctxt.setemptyline = 0;

    char linebuf[NBUF];
    linebuf[0] = 0;
    if (!ctxt.setemptyline)
    {
        int displaynumber = 1;
        while loop {
    	    char *prtline = 0; size_t prtlinen = 0; ssize_t r;
    	    r = getline(&prtline, &prtlinen, stdin);
        	throwngerrno(r);

        	if (strlen(linebuf) + strlen(prtline) < NBUF) {
        		strcat(linebuf + strlen(linebuf), prtline);
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
    else {
    	linebuf[0] = '\n';
    	linebuf[1] = 0;
    	ctxt.setemptyline = 0;
    }
    char *line = linebuf;

    char aouttxtpath[NBUF] = "";
    snprintf(aouttxtpath, NBUF, "%s/log.txt", ctxt.rootworkdir);
    fputsclose(line, fopen(aouttxtpath, "a"));

    if (!ctxt.syssh && 0 == strncmp(line, "#exit", 5)) {
    	exit(0);
    }

    {
        if (ctxt.syssh && 0 == strncmp(line, "exit", 4)) {
    	    ctxt.syssh = 0;
    	    line+= 4;
        }

        if (!ctxt.syssh && 0 == strncmp(line, "$ ", 2)) {
        	ctxt.syssh = 1;
        	line += 2;
        }

        void *srcfile = fopen(ctxtmwf("main.c"), "w");
		fprintf(srcfile, "#include \"main.h\"\n");
		fprintf(srcfile, "\n");
		fprintf(srcfile, "char *lastcmd = \"%s\";\n", 
		        escapecstr(ctxt.lastline, linebuf_tn));
		fprintf(srcfile, "int syssh = %d;\n", ctxt.syssh);
		fprintf(srcfile, "char *workdir = \"%s\";", ctxt.rootworkdir);
		fprintf(srcfile, "\n");
		fprintf(srcfile, "int main(int argc, char **argv) {\n");
		fprintf(srcfile,     "MAIN_BEGIN\n");

		for (unsigned long i = 1; i < strlen(line); ++i) {
			if (line[i] == '\n' && line[i-1] != '\\')
			    line[i] = ' ';
		}

		if (0 == strncmp(line, "cd ", 3)) {
			line += 3;
			line[strlen(line) - 1] = 0;
			char path[NBUF];
			snprintf(path, NBUF, "%s/cwd.txt", ctxt.rootworkdir);
			void *f = fopen(path, "w");
			fprintf(f, "%s/%s/\n", cwd, line);			
			fclose(f);
			loadcwd(ctxt.rootworkdir);
		}
		else {
		    if (ctxt.syssh) fprintf(srcfile, "system(\"%s\");", line);
			else            fprintf(srcfile, "%s", line);
				
		}
        
		fprintf(srcfile,     "\nMAIN_END");
		fprintf(srcfile, "}");	
	
		fclose(srcfile);

		{
			sh, "rm -f %s", ctxtmwf("a.out"), endsh;
			(sh, "gcc %s -o%s", ctxtmwf("main.c"), ctxtmwf("a.out"), endsh) && (
				0
			);
			{
				/*
				if (sh, "mv %s %s", ctxt.rootworkdir, mlinebufprintf("%s%s", ctxt.rootworkdir, ".err"), endsh)
				{
					printf("mv rootworkdir rootworkdir.err failed");
				}
				else
				{
					if (sh, "mv %s %s", 
					    mlinebufprintf("%s%s", ctxt.rootworkdir, ".bak"), ctxt.rootworkdir,
					    endsh)
					{
					    printf("mv rootworkdir.bak rootworkdir failed");
					}
					else
					{
						printf("rootworkdir restored to last working version.");
					}
				}
				*/
			}
		}
		sh, ctxtmwf("a.out"), endsh;

		sh, "cp -r %s %s", ctxt.rootworkdir, mlinebufprintf("%s.bak", ctxt.rootworkdir), endsh;


		//char *stdoutpath = mlinebufprintf("%s/%s", ctxt.rootworkdir, "a.out.txt");
		char cmdouttxt[NBUF * 80 * 128] = "";
		//fgetsclose(cmdouttxt, sizeof cmdouttxt, fopen(stdoutpath, "r"));
		printf("%s", cmdouttxt);

		strcpy(ctxt.lastline, linebuf);
    }
  } 
}
