#define MAIN_BEGIN runbatch();
#define MAIN_END mvbatch(); statusprint(syssh);

#warning system() does not wait for command to exit!

#define NBUF 512

#define ROOT "/data/data/com.termux/files/home/prj/bytesh/"
#define ROOTLEN strlen(ROOT)

#include "stdlib.h"
#include "unistd.h"
#include "string.h"

#include "cnslutil.h"

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

void statusprint(int issyssh)
{
	char cwd[NBUF]; getcwd(cwd, NBUF);
    if (1)
    {
    	printf("\n[%s]\n",  cwd);
    	if (issyssh) {
    		printf(".sh (priv) $ ");
    	} else {
    		printf(".c (priv) $ ");
    	}
    }
}


#define batch edit batchpath _

void submain(int argc, char **argv)
{
	printf("Hello submain");
}

char *memcmov(char *dst, char *src, int c, size_t n)
{
	char tmp[n];
	        memccpy(tmp, src, c, n);
	return  memccpy(dst, tmp, c, n);
}

char *strnmov(char *dst, char *src, size_t n)
{
	return memcmov(dst, src, 0, n);
}

char *strchrnul(char *s, int c)
{
	char *res = strchr(s, c);
	if (!res)
		return s + strlen(s);
	return res;
}

char *fgetsclose(char *s, int n, FILE *f)
{
	char *result = s;
	while ((n > 0) && fgets(s, n, f))
	{
		n-= strlen(s);
		s+= strlen(s);
	}
	fclose(f);
	return result;
}

#define breakpt ; {char c[8]; fgets(c, 8, stdin);};

#define LOADBUFN 2048
char *loads(char *filename)
{
	return fgetsclose(malloc(LOADBUFN), LOADBUFN, fopen(filename, "r"));
}

void test()
{
}

char *escapeccstr(char *s, int buflen, int c, int r)
{
	if (buflen < (int)strlen(s) * 2)
	{
		printf("Error at %s:%d\n", __FILE__, __LINE__);
		exit(1);	
	}

    char *p = s;
    char *end = p + strlen(p);
    while ((p = strchrnul(p, c)) != end)
    {
    	strnmov(p + 1, p, buflen);
    	p[0] = '\\';
    	p[1] = r;
    	p+= 2;
    	end = p + strlen(p);
    }
	return s;
}



void mkdir(char *path)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "mkdir %s", path);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define mkdir mkdir (

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
	    sys "git add *" _
	    sys "git add */*" _
	    sys "git commit -m untitled" _
	echosys "git status" _
	//echosys "git log" _
}
#define gitupdate gitupdate();

#define switchstr
#define casestr if ( !strcmp(

void man(char *topic) {
	if (0//!strcmp(topic, "fopen")
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
	else if (!strcmp(topic, "memcmov")) 
	{
		printf("NAME\n");
		printf("       memcmov - move memory area\n");
		printf("\n");
		printf("LIBRARY\n");
		printf("       Extended Standard C library\n");
		printf("\n");
		printf("SYNOPSIS\n");
		printf("       #include <stringext.h>\n");
		printf("\n");
		printf("       void *memcmov(void dst[.n], \n");
		printf("                     void const src[.n], int c,\n");
		printf("                     size_t n);\n");
		printf("\n");
		printf("DESCRIPTION\n");
		printf("       The memcmov() function copies no more than\n");
		printf("       `n` bytes from memory area `src` to memory\n");
		printf("       area `dst`, stopping when the character\n");
		printf("       `c` is found (`c` is copied).\n");
		printf("\n");
		printf("       The memory areas may overlap.\n");
		printf("\n");
		printf("RETURN VALUE\n");
		printf("       The memcmov() function returns a pointer to\n");
		printf("       the next character in `dst` after `c`, or\n");
		printf("       NULL if `c` was not found in the first `n`\n");
		printf("       characters of `src`.\n");
		printf("\n");
	}
	if (!strcmp(topic, "fgets"))
	{
		printf("NAME\n");
		printf("       fgets - input of strings\n");
		printf("\n");
		printf("LIBRARY\n");
		printf("       Standard C library\n");
		printf("\n");
		printf("SYNOPSIS\n");
		printf("       #include <stdio.h>\n");
		printf("\n");
		printf("       char *fgets(char s[.n], int n, FILE *f)\n");
		printf("\n");
		printf("DESCRIPTION\n");
		printf("       fgets() reads in at most one less than\n");
		printf("       `size` characters from `f` and stores them\n");
		printf("       into the buffer pointed to by `s`. Reading\n");
		printf("       stops after an EOF or a newline. If a new-\n");
		printf("       line is read, it is stored into the buffer.\n");
		printf("       A terminating null byte ('\\0') is stored\n");
		printf("       after the last character in the buffer.\n");
		printf("       \n");
		printf("RETURN VALUE\n");
		printf("       fgets() returns `s` on success, and NULL on\n");
		printf("       error or when end of file occurs while no\n");
		printf("       characters have been read.\n");
		printf("       \n");
		printf("       \n");
		printf("       \n");
		printf("       \n");
		printf("       \n");


	}
	else
	{
		char cmd[NBUF];
		snprintf(cmd, NBUF, "man %s", topic);
		system(cmd);
	}
}
#define man man (

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

#define batchnextpath in(                 \
    memcpy(nbufarr[0], ROOT, ROOTLEN),    \
    (strcat), "/run/batch.h.next")
#define batchpath     in(                 \
    memcpy(nbufarr[1], ROOT, ROOTLEN),    \
    (strcat), "/run/batch.h")
void mvbatch()
{
    //void cp(char *, char*);
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


