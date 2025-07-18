
#define batch edit batchpath _

char nbufarr[16][NBUF];


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

#define switchstr
#define casestr if ( !strcmp(

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


