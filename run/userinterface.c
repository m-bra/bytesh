
#include <termios.h>

int echoflag()
{
	return ECHO;
}

#include <signal.h>
#include <errno.h>

#include <unistd.h>
#include "main.h"

#include "userinterface.h"

struct termios uirestoreval;

int unbufreadc(int);

SECTION TEXT


FUNCTION struct termios uiunbuffered()

def struct termios old_tio, new_tio;        
	tcgetattr(STDIN_FILENO, &old_tio);    
	new_tio = old_tio;    
	// Disable canonical mode (line buffering) and echoing    
	new_tio.c_lflag &= (~ICANON & ~echoflag());    
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);    
	return old_tio;


FUNCTION void uibuffered()

def 
    struct termios new_tio;   
	tcgetattr(STDIN_FILENO, &uirestoreval);    
	new_tio = uirestoreval;    
	// Disable canonical mode (line buffering) and echoing    
	new_tio.c_lflag |= (ICANON | echoflag());    
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);    

FUNCTION void uirestore(struct termios old_tio)

def tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);    


FUNCTION char *mgetline(char *beginlinefmt)

def
	
stm char *pagebuf = mallocaddpagebuf; pagebuf[0] = 0;
stm int linen = 1;
stm char lastchar = ' ';
stm int cmdlogline = cmdlogn() - 2;
    
rep 
blk

stm fflush(getstdout());
stm int c = unbufreadc(STDIN_FILENO);
stm int is_control_key = c == BACKSPACE_CONTROL_KEY || c == ESC;

iff c == eof() 
thn return pagebuf;

iff c == BACKSPACE_CONTROL_KEY
 && strlen(pagebuf) > 0
 && pagebuf[strlen(pagebuf) - 1] != '\n' 
thn blk
    stm pagebuf[strlen(pagebuf) - 1] = 0;
    stm printf("\x1B[1D \x1B[1D"); fflush(getstdout());
    blk_end

iff c == ESC
 && unbufreadc(STDIN_FILENO) == ARROW_UP_SEQ[1]
 && unbufreadc(STDIN_FILENO) == ARROW_UP_SEQ[2]
thn blk    
    stm linebuf_t mem;
    chr *buf = &mem[0];
    stm void cmdlogat(int, linebuf_t *);
    rep blk cmdlogat(cmdlogline--, &mem);
        iff buf[strspn(buf, " ")] == '>'
        thn continue;
	iff strstr(buf, "$")
	thn break;
	blk_end
    stm EVALECHO( es$ buf $; )
    stm buf = strstr(buf, "$") + 1;
    iff strlen(buf) > 80
    thn buf[79] = '\0';
    //stm printf("Hello");ln;
    for range(0, strlen(buf))
    iff buf[i] == '\n'
    thn buf[i] =   ' ';

    for range(0, strlen(pagebuf))
    stm printf("%s %s", ESCSEQ_CURSOR_BACK, ESCSEQ_CURSOR_BACK); 
    stm fflush(getstdout());

    stm *stpncpy(pagebuf, buf, linebuf_tn) = 0;
    stm printf("%s", pagebuf);
    blk_end


iff c == '\t'
 && !strncmp(pagebuf, "us", 2)
thn blk
    //nil tab_triggers()
        blk
        for range(0, strlen(pagebuf))
	    printf("%s %s", ESCSEQ_CURSOR_BACK, ESCSEQ_CURSOR_BACK); 
	char *sznew = "userinterfaceh";
	strcpy(pagebuf, sznew);
	printf("%s", sznew); fflush(getstdout());
	blk_end
    //tab_triggers();
    blk_end

iff c == c && !is_control_key
thn blk
    stm putc(c, getstdout());
	ifn strlen(pagebuf) + 1 < pagebuf_tn
	the pagebuf[strlen(pagebuf) + 0] = c;
    stm pagebuf[strlen(pagebuf) + 1] = 0;

    //nil automatic_triggers()
        blk
	iff !strncmp(pagebuf, "cd", 3)
	thn ign 
	    blk
	    stm strcpy(pagebuf, "# cd");
            stm printf("\x1B[1D\x1B[1D# cd"); fflush(getstdout());
	    blk_end
        blk_end
    //stm automatic_triggers();        	
    blk_end

iff c == '\n' && lastchar != '\\'
thn return pagebuf;

iff c == '\n'
thn printf(beginlinefmt, ++linen);

stm fflush(getstdout());

iff !is_control_key
thn lastchar = c;

stm continue;
err:
stm printf("Error at %s:%d: Buffer overflow.\n", __FILE__, __LINE__);
stm exit(1);
blk_end



FUNCTION void uiexample_rendered(int i)

def
	unbuf (
		printf("test %s", "hello");
	)




FUNCTION void uitest()

def unbuf (
		char input[4];
		int n = read(STDIN_FILENO, input, 1);
	//iff n < 1
	//thn break;
		printf("read (int) %d \n", (int) input[0]);
	)


FUNCTION int unbufreadc(int fd) 
def int c; unbuf( c = readc(STDIN_FILENO); ) return c;


SECTION DATA
