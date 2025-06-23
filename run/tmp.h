
#define _XOPEN_SOURCE 700
#include <stdio.h> 
#include <sys/types.h> 
#include <dirent.h> 

int dirtest (void) {   
    DIR *dp;   
    struct dirent *ep;        
    dp = opendir ("./");   
    if (dp != NULL)   {     
    	while ((ep = readdir (dp)) != NULL)       
    		puts (ep->d_name);                
    	(void) closedir (dp);     
    	return 0;   
    } 
    else   
    {     
    	perror ("Couldn't open the directory");     
    	return -1;   
    } 
}

#define jsdownload "function download(filename, text) {     var pom = document.createElement('a'); pom.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(text));     pom.setAttribute('download', filename);     if (document.createEvent) {         var event = document.createEvent('MouseEvents');         event.initEvent('click', true, true);         pom.dispatchEvent(event);     }     else {         pom.click();     } }"


void tsacomplete()
{
	fputsclose("0", fopen(TSAROOT("/index.txt"), "w"));
	mv, "main.*.ppm", "bak", endsh;
	for (int i = 0; i < 200; ++i) {sh, TSAROOT("./a.out"), endsh; ed(i);}
	ffmpegi, "main.%d.ppm", "main.webm", endsh;
}
#define tsacomplete tsacomplete()


char *squaretext =
"HELLO THIS IS A TEST MSG\n"
  "HELLO THIS IS A TEST MSG\n"
  "HELLO THIS IS A TEST MSG\n"
  "HELLO THIS IS A TEST MSG\n"
  "HELLO THIS IS A TEST MSG\n"
  "HELLO THIS IS A TEST MSG\n"
  "HELLO THIS IS A TEST MSG\n"                                                                                 "HELLO THIS IS A TEST MSG\n"                                                                                 "HELLO THIS IS A TEST MSG";


void tsaframesold()
{
	char muttext[pagebuf_tn];
	strncpy(muttext, squaretext, pagebuf_tn);
	muttext[pagebuf_tn - 1] = 0;

	for (int i = 0; i < strlen(muttext); ++i)
	{
		if (muttext[i] == NL) muttext[i] = ' ';
	}
	
	for (int i = 0; i < strlen(muttext); ++i)
	{
	   for (int j = i; j < strlen(muttext); ++j)
       {
       	    
	   }
	   { 
	   	   char filename[linebuf_tn];
	   	   filename[0] = 0;
	   	   snprintf(filename, linebuf_tn, "/main.%04d", i);
	       tsa(muttext, filename);
	   }
	   strncpy(muttext, squaretext, pagebuf_tn);
	   muttext[pagebuf_tn - 1] = 0;
    }
}
#define tsaframes tsaframes()

void tsaf()\
{
  
  char file[pagebuf_tn * 64];\
  file[0] = 0;\
  char *fileline; breakpt;
  FILE *f = fopen("text.txt.out", "r"); breakpt;
  int i = 0;
  while (fileline = fgetm(32 * linebuf_tn, f))\
  {\
    if (strlen(file) + strlen(fileline) + 1 > pagebuf_tn * 64)
    	printf("Error at %s:%d\n", __FILE__, __LINE__), exit(1);
    strcat(file, fileline);
    for (int i = 0 ; i < strlen(fileline); ++i)
    	ed(fileline[i]);
    ++i;
    if (i == 10)
    	break;
  }\
  es(file);\
  tsa(file, "/main.ppm");\
  fclose(f);//*/
}


#define edit2025h printf("%s", "Found in: $ tmph\n")
#define edit2025 


