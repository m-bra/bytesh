#ifndef RUN_MAIN_H_INCLUDED
#define RUN_MAIN_H_INCLUDED


#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>

#include "mainsys.h"
#include "stdlibext.h"
#include "stringext.h"
#include "stringutil.h"
#include "stdioext.h"
#include "unistdext.h"
#include "mathext.h"

extern int main_interactive;

void main_begin(int argc, char **argv);
void main_init(int argc, char **argv);
void statusprint(char *);
void sighandle(int);

txt

#define GLOBAL_INDENT ""
//#define GLOBAL_INDENT "                           "

#define loctag

SECTION DATA

extern int ORIGINAL_STDOUT_FILENO;

SECTION TEXT

#define MAIN_BEGIN \
	    \
	    main_init(argc, argv); \
    
#define MAIN_END ;\
        dup2(ORIGINAL_STDOUT_FILENO, STDOUT_FILENO);\
	    if (main_interactive) statusprint(rootworkdir);
	//iff main_interactive 
	//thn {edit, ROOTC("/run/a.out.txt"), endsh;}

SECTION DATA

extern int isfirstcmd;
extern char *rootworkdir;
void cmdlogat(int, linebuf_t *);


#include ".//userinterface.h"

#define PROMPT "0x%04X.priv.c %s $ "

stm int cmdlogn();

SECTION TEXT

SECTION DATA

extern int counter;

SECTION TEXT

dat

#include "cnslutil.h"
#include "misc.h"

txt

FUNCTION inline void unused_main()
blk blk_end

#include "projects.h"
#include "tmp.h"


#endif
