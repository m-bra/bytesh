#define MAIN_BEGIN runbatch();
#define MAIN_END mvbatch(); statusprint(syssh);

#warning system() does not wait for command to exit!

#define NBUF 512

#define ROOT "/data/data/com.termux/files/home/prj/bytesh/"
#define ROOTLEN strlen(ROOT)

#include "stdlib.h"
#include "unistd.h"
#include "string.h"

//#include "todo.h"

#define ln ;printf("\n");

#define tmuxhelp printf("ctrl+b+\" \nctrl+b+%%\nctrl+b meta+arrow\n");
#define mainh sys "micro /data/data/com.termux/files/home/prj/bytesh/run/main.h" _
#define vncserver sys "vncserver -localhost" _
#define prootdistro sys "proot-distro login archlinux" _
#define tmux sys "tmux" _
#define ls sys "ls" _

char nbufarr[16][NBUF];

#define in(a, f, b) f ( a , b )

#define batchnextpath in(                 \
    memcpy(nbufarr[0], ROOT, ROOTLEN),    \
    (strcat), "/run/batch.h.next")
#define batchpath     in(                 \
    memcpy(nbufarr[1], ROOT, ROOTLEN),    \
    (strcat), "/run/batch.h")
void mvbatch()
{
    void cp(char *, char*);
	//cp(batchnextpath, batchpath);
	char cmd[NBUF];
	snprintf(cmd, NBUF, "echo '' > %s", batchnextpath);
	//system(cmd);
}

void runbatch()
{
    //#include "batch.h"
    //system("mv batch.h batch.h.bak");
    //system("touch batch.h");
}

void statusprint(int issyssh)
{
		char cwd[NBUF]; getcwd(cwd, NBUF);
			char batch[NBUF];                                                     	void *batchfile;                                                      	fgets(batch, NBUF, batchfile = fopen(batchpath, "r"));            
	int dobatch = strlen(batch);                                          	fclose(batchfile);
	dobatch = 0;

    if (!dobatch)
    {
    	printf("\n[%s]\n",  cwd);
        printf("$ %s", issyssh ? "$ " : "");
    }
    else {

    	printf("[batch]");
    }



}


#define batch edit batchpath _

void submain(int argc, char **argv)
{
	printf("Hello submain");
}

void man(char *topic)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "man %s", topic);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define man man (

void mv(char *from, char *to)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "mv %s %s", from, to);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define mv mv (

void cp(char *from, char *to)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "cp %s %s", from, to);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define cp cp (

void rm(char *filename)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "rm %s", filename);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define rm rm (

void cat(char *filename)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "cat %s", filename);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define cat cat (

void touch(char *s)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "touch %s", s);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define touch touch (

void diff(char *from, char *to)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "diff %s %s", from, to);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define diff diff (

//#define syssh syssh();

void editcompiler()
{
	system("micro /data/data/com.termux/files/home/prj/bytesh/main.c");
    system("gcc   /data/data/com.termux/files/home/prj/bytesh/main.c \
               -o /data/data/com.termux/files/home/prj/bytesh/a.out");
	exit(0);
}

#define editcompiler editcompiler();

void printallascii(int from, int to)
{
	for (int i = from; i < to; ++i)
	{
		printf("- %c - ", i);
		if (!(i % 24)) printf("\n");
	}
	printf("\n");
}
#define printallascii printallascii('1', '~');

void testwrite(char *path)
{
//	FILE *mainhfile = fopen("/data/data/com.termux/files/home/prj/c/bytesh/run/main.h", "w");
    char filebuf[102400];
	FILE *f = fopen(path, "w");
    
	fclose(f);
}

void micro(char const *path)
{
	char buf[512];
	snprintf(buf, 512, "micro %s", path);
	system(buf);
	// TODO: undefined escape rules in param strings
}

#define edit micro (
#define _ ) ;
#define sys system (

void echosys(char const *cmd)
{
    printf("\n[auto]\n");
	printf("$ %s\n\n", cmd);
	system(cmd);
}
#define echosys echosys (

void gitupdate() {
	echosys "git add *" _
	echosys "git add */*" _
	echosys "git commit -m untitled" _
	echosys "git status" _
	echosys "git log" _
}
#define gitupdate gitupdate();

#define switchstr
#define casestr if ( !strcmp(

void manpriv(char *topic) {
	if (1//!strcmp(topic, "fopen")
	//|| (!strcmp(topic, "fdopen"))
	|| (!strcmp(topic, "freopen")))
	{
		printf("#include <stdio.h>\n");
		printf("FILE *freopen(char *path, char *mode, FILE *f);\n");
		printf("\n");
		printf("The freopen() function opens the file whose name is\n");
		printf("the string pointed to by `path` and associates the\n");
		printf("stream pointed to by `f` with it. The original\n");
		printf("stream (if it exists) is closed.\n");
		printf("\n");
		printf("On failure, NULL is returend and `errno` is set to\n");
		printf("indicate the error.\n");
	
	}
}
#define manpriv manpriv (

void lines(int n) {
  for (
    int i = 0;
    i < n;
    ++i
  ) {
    printf("\n"); 	
  }
}

#define LINESPERPAGE 8

void draw(char n) {
  for (
    int i = 0;
    i < LINESPERPAGE;
    ++i
  ) {
    for (
  	  int j = 0;
  	  j < 10;
  	  ++j
    ) { 
  	  printf("%c ", n);
    } 
    printf("\n");
  }
}

void cycle() {
  char c = 'A';
  int i = 0;
  while (1) {
    //char buf[8];
    //scanf("%7s", buf);
    draw(c);
    c += 1;
    if (c == 'Z') {
    	c = 'A';
    	i += 1;
    }
    if (i == 2)
      break;
    system (
      "sleep 0.2"
    );	
  }
}

