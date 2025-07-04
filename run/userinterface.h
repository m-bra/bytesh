#include "main.h"

#ifndef USERINTERFACEHINCLUDED
#define USERINTERFACEHINCLUDED
#define userinterfaceh edit, ROOTC("/run/userinterface.h"), endsh
#define userinterfacehadd hadd("userinterface")
#define userinterfacehaddfn(ident) haddfn("userinterface", ident)
#define userinterfacehadddef(ident) hadditem("userinterface", ident, 1)

#define clear sh, "clear", endsh

#define ARROW_CONTROL_KEYh printf("%s", "Found in: $ userinterfaceh\n")
#define ARROW_CONTROL_KEY 27
#define ESC '\x1B'
#define ARROW_UP_SEQ "\x1B[A"
#define ESCSEQ_ARROW_UP
#define ESCSEQ_CURSOR_BACK "\x1B[1D"
#define BACKSPACE_CONTROL_KEY 127

#include <termios.h>
#include <unistd.h>

SECTION TEXT

SECTION DATA

	struct termios uirestoreval;

SECTION TEXT

FUNCTION struct termios uiunbuffered()

def struct termios old_tio, new_tio;        
	tcgetattr(STDIN_FILENO, &old_tio);    
	new_tio = old_tio;    
	// Disable canonical mode (line buffering) and echoing    
	new_tio.c_lflag &= (~ICANON & ~ECHO);    
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);    
	return old_tio;


FUNCTION void uibuffered()

def 
    struct termios new_tio;   
	tcgetattr(STDIN_FILENO, &uirestoreval);    
	new_tio = uirestoreval;    
	// Disable canonical mode (line buffering) and echoing    
	new_tio.c_lflag |= (ICANON | ECHO);    
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);    

FUNCTION  void uirestore(struct termios old_tio)

def tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);    

#define uicallunbuffn(f, ...) uiunbuffered(); f(uiunbufcall, __VA_ARGS__); uirestore();

#define uiunbuf(t, ident, t2, par) \
    t ident(t2 par, ...)\
    {\
        va_list args;\
        va_start(args, par);\
        struct termios old_tio = uiunbuffered();\
        t uiunbuf_##ident(int, va_list);\
        uiunbuf_##ident(par, args);\
        uirestore(old_tio);\
        va_end(args);\
    }\
    t uiunbuf_##ident(t2 par, va_list args)
    
#define exec

#define unbuf(inner) {\
  struct termios old_tio = uiunbuffered();\
  { inner }\
  uirestore(old_tio);\
}


FUNCTION void uiexample_rendered(int i)

def
	unbuf (
		printf("test %s", "hello");
	)


#define mgetescline mgetline


FUNCTION void uitest()

def unbuf (
		char input[4];
		int n = read(STDIN_FILENO, input, 1);
	//iff n < 1
	//thn break;
		printf("read (int) %d \n", (int) input[0]);
	)

#define uitest uitest()

FUNCTION int unbufreadc(int fd) 

def int c; unbuf( c = readc(STDIN_FILENO); ) return c;

FUNCTION char *mgetline(char *beginlinefmt) loctag

def
	
stm char *pagebuf = mallocaddpagebuf; pagebuf[0] = 0;
stm int linen = 1;
stm char lastchar = ' ';
stm int cmdlogline = 0;// cmdlogn();
    
rep 
blk

stm fflush(stdout);
stm int c = unbufreadc(STDIN_FILENO);
stm int is_control_key = c == BACKSPACE_CONTROL_KEY || c == ESC;

iff c == EOF 
thn return pagebuf;

iff c == BACKSPACE_CONTROL_KEY
 && strlen(pagebuf) > 0
 && pagebuf[strlen(pagebuf) - 1] != '\n' 
thn blk
    stm pagebuf[strlen(pagebuf) - 1] = 0;
    stm printf("\x1B[1D \x1B[1D"); fflush(stdout);
    blk_end

iff c == ESC
 && unbufreadc(STDIN_FILENO) == ARROW_UP_SEQ[1]
 && unbufreadc(STDIN_FILENO) == ARROW_UP_SEQ[2]
thn blk             
    stm linebuf_t buf;
    stm cmdlogat(cmdlogline--, &buf);
	//stm printf("Hello");ln;
	for range(0, strlen(pagebuf))
	iff buf[i] == '\n'
	thn buf[i] =   ' ';

    for range(0, strlen(pagebuf))
    stm printf("%s %s", ESCSEQ_CURSOR_BACK, ESCSEQ_CURSOR_BACK); 
    stm fflush(stdout);

    stm *stpncpy(pagebuf, buf, linebuf_tn) = 0;
    stm printf("%s", pagebuf);
    blk_end


iff c == '\t'
 && !strncmp(pagebuf, "us", 2)
thn blk
    nil tab_triggers()
    s   blk
    s   for range(0, strlen(pagebuf))
	s   s   printf("%s %s", ESCSEQ_CURSOR_BACK, ESCSEQ_CURSOR_BACK); 
	s   s   char *sznew = "userinterfaceh";
	s   s   strcpy(pagebuf, sznew);
	s   s   printf("%s", sznew); fflush(stdout);
	s   blk_end
    s   tab_triggers();
    blk_end

iff c == c && !is_control_key
thn blk
    stm putc(c, stdout);
	ifn strlen(pagebuf) + 1 < pagebuf_tn
	the pagebuf[strlen(pagebuf) + 0] = c;
    stm pagebuf[strlen(pagebuf) + 1] = 0;

    nil automatic_triggers()
        blk
		iff !strncmp(pagebuf, "cd", 3)
		thn blk
		    stm strcpy(pagebuf, "# cd");
	        stm printf("\x1B[1D\x1B[1D# cd"); fflush(stdout);
		    blk_end
	    blk_end
	stm automatic_triggers();        	
    blk_end

iff c == '\n' && lastchar != '\\'
thn return pagebuf;

iff c == '\n'
thn printf(beginlinefmt, ++linen);

stm fflush(stdout);

iff !is_control_key
thn lastchar = c;

stm continue;
err:
stm printf("Error at %s:%d: Buffer overflow.\n", __FILE__, __LINE__);
stm exit(1);
blk_end

FUNCTION void unused_end_ui()
blk end_blk

#endif
