#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "unistd.h"

#define NBUF 512

#define throwngerrno(x)                     \
    if (x < 0) {                            \
        printf("Error at ");                \
  	    printf("%s:", __FILE__);            \
  		printf("%d\n", __LINE__);           \
  		printf("%s\n", strerror(errno));    \
  		exit(1);                            \
  	}                                       \
//

void loadcwd(char *workdir)
{
    char path[NBUF]; snprintf(path, NBUF, "%s/cwd.txt", workdir);
//    printf("path = '%s'\n", path);
    FILE *f = fopen(path, "r");
    char line[NBUF]; fgets(line, NBUF, f);
    line[strlen(line) - 1] = 0;
//    printf("line = '%s'\n", line);
    int r = chdir(line);
    if (r < 0) printf("cd: error\n");
    fclose(f);
}

int main(int argc, char **argv) {
  int syssh = 0;
  
  char *workdir = argv[1];

  if (argc < 2) { printf("%s: %s %s%s\n", "Usage", argv[0], "<workdir>", ""); return 1; }

  char a[NBUF]; snprintf(a, NBUF, "%s/main.c", workdir);
  char *srcfilename = a;

  char b[NBUF]; snprintf(b, NBUF, "%s/a.out", workdir);
  char *outfilename = b;

  char c[NBUF]; snprintf(c, NBUF, "%s/batch.h", workdir);
  char *batchfilename = c;

  int setemptyline = 1;

  while ( 1 ) {
    loadcwd(workdir);
    char cwd[NBUF]; getcwd(cwd, NBUF);
    
    // printf("%s $ ", cwd); if (syssh) printf("$ ");

    setemptyline = 0;

    char batch[NBUF];
    void *batchfile; 
    fgets(batch, NBUF, batchfile = fopen(batchfilename, "r"));
    int dobatch = strlen(batch);
    fclose(batchfile);
    dobatch = 0;

    char *line;
    char *linemem = 0; size_t linelen; ssize_t r;
    if (!setemptyline)
    {
    	r = getline(&linemem, &linelen, stdin);
        line = linemem;
    }
    else {
    	line = "\n";
    	linelen = strlen(line);
    	r = 0;
    	setemptyline = 0;
    }
  	throwngerrno(r);

  	if (dobatch && strlen(line) > 1)
  	{
  		printf("Error: Expected empty command expected after batch commands.");
    	printf("\n");
    	exit(1);  		
  	}


    if (!syssh && 0 == strncmp(line, "#exit", 5)) {
    	exit(0);
    }

    {
        if (syssh && 0 == strncmp(line, "exit", 4)) {
    	    syssh = 0;
    	    line+= 4;
        }

        if (!syssh && 0 == strncmp(line, "$ ", 2)) {
        	syssh = 1;
        	line += 2;
        }
    
        void *srcfile = fopen(srcfilename, "w");
		fprintf(srcfile, "#include \"main.h\"\n");
		fprintf(srcfile, "#define syssh %d\n", syssh);
		fprintf(srcfile, "int main(int argc, char **argv) {\n");
		fprintf(srcfile,     "MAIN_BEGIN\n");

		for (unsigned long i = 0; i < strlen(line); ++i) {
			if (line[i] == '\n')
			    line[i] = ' ';
		}

		if (0 == strncmp(line, "cd ", 3)) {
			line += 3;
			line[strlen(line) - 1] = 0;
			char path[NBUF];
			snprintf(path, NBUF, "%s/cwd.txt", workdir);
			void *f = fopen(path, "w");
			fprintf(f, "%s/%s/\n", cwd, line);			
			fclose(f);
		}
		else {
		    if (syssh) fprintf(srcfile, "system(\"%s\");", line);
			else       fprintf(srcfile, "%s", line);
				
		}
        
		fprintf(srcfile,     "\nMAIN_END");
		fprintf(srcfile, "}");	
	
		fclose(srcfile);
	
		char cmd[NBUF];
		snprintf(cmd, NBUF, "rm -f %s", outfilename);
		system(cmd);
	
		snprintf(cmd, NBUF, "gcc %s -o%s", srcfilename, outfilename);
		system(cmd);
	
		system(outfilename);	
    }

  	if (linemem) free(linemem);
  } 
}
