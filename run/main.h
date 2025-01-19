#define MAIN_BEGIN
#define MAIN_END
#define ROOT "/data/data/com.termux/files/home/prj/c/bytesh/"

#include "stdlib.h"
#include "unistd.h"
#include "string.h"

#define mainh system("micro /data/data/com.termux/files/home/prj/c/bytesh/run/main.h");

#define syssh syssh();

void editcompiler()
{
	system("micro /data/data/com.termux/files/home/prj/c/bytesh/main.c");
    system("gcc   /data/data/com.termux/files/home/prj/c/bytesh/main.c \
               -o /data/data/com.termux/files/home/prj/c/bytesh/a.out");
	exit(0);
}

#define editcompiler editcompiler();

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
}

#define edit micro (
#define _ ) ;
#define sys system (

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

