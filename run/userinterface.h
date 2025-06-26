#ifndef USERINTERFACEHINCLUDED
#define USERINTERFACEHINCLUDED
#define userinterfaceh edit, ROOTC("/run/userinterface.h"), endsh
#define userinterfacehadd hadd("userinterface")
#define userinterfacehaddfn(ident) haddfn("userinterface", ident)
#define userinterfacehadddef(ident) hadditem("userinterface", ident, 1)

#define clear sh, "clear", endsh

#define ARROW_CONTROL_KEYh printf("%s", "Found in: $ userinterfaceh\n")
#define ARROW_CONTROL_KEY 27
#define BACKSPACE_CONTROL_KEY 127

#include "main.h"
#include <termios.h>
#include <unistd.h>

struct termios uirestoreval;

struct termios uiunbuffered() {   
	struct termios old_tio, new_tio;        
	tcgetattr(STDIN_FILENO, &old_tio);    
	new_tio = old_tio;    
	// Disable canonical mode (line buffering) and echoing    
	new_tio.c_lflag &= (~ICANON & ~ECHO);    
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);    
	return old_tio;
}

void uibuffered() {   
	struct termios new_tio;   
	tcgetattr(STDIN_FILENO, &uirestoreval);    
	new_tio = uirestoreval;    
	// Disable canonical mode (line buffering) and echoing    
	new_tio.c_lflag |= (ICANON | ECHO);    
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);    
}

void uirestore(struct termios old_tio)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);    
}

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

exec uiunbuf(void, uiexample, int, x)
{
	ed(x);
}

#define unbuf(inner) {\
  struct termios old_tio = uiunbuffered();\
  { inner }\
  uirestore(old_tio);\
}

void uiexample_rendered(int i)
{
	unbuf (
		printf("test %s", "hello");
	)
}//*/


#define mgetescline mgetline

void uitest()
{
	unbuf (
		char input[4];
		int n = read(STDIN_FILENO, input, 1);
	//iff n < 1
	//thn break;
		printf("Keycode %d \n", (int) input[0]);
	)
}
#define uitest uitest()

char *mgetline(char *beginlinefmt) 
{
	fflush(stdout);
	
	char *pagebuf = mallocaddpagebuf;
	
    int displaynumber = 1;
    char lastchar = ' ';
    rep {
    stm char c[2];
    stm c[1] = 0;
    stm char *prtline = c; size_t prtlinen = 1; ssize_t r;
	stm int n;
    stm unbuf( n = read(STDIN_FILENO, prtline, 1); )
        
	iff n < 1 
	thn break;

	stm int is_control_key = *c == BACKSPACE_CONTROL_KEY;

	iff *c == BACKSPACE_CONTROL_KEY 
	 && strlen(pagebuf) > 0
	 && pagebuf[strlen(pagebuf) - 1] != '\n' 
	thn {
    stm stm pagebuf[strlen(pagebuf) - 1] = 0;
	stm stm clear; printf("%s", pagebuf); fflush(stdout);
	stm }

	iff !is_control_key
	thn {
	stm stm printf("%c", *c);
        
		    //r = getline(&prtline, &prtlinen, stdin);
	    	//throwngerrno(r);
	    	
	     	if (strlen(pagebuf) + strlen(prtline) < pagebuf_tn) {
	    		strcat(pagebuf + strlen(pagebuf), prtline);
	    	} else {
	    		printf("Buffer overflow.\n");
	    		exit(1);
	    	}
	    }

	
	iff (*c == '\n' && lastchar != '\\')
	thn {break;}
	
        //if (strlen(prtline) < 2 
        //|| (prtline[strlen(prtline) - 2] != '\\'))
  	    //    break;
  	    //free(prtline);

  	    if (*c == '\n')
            ;//printf(beginlinefmt, ++displaynumber);
        fflush(stdout);

	iff !is_control_key
	thn lastchar = *c;
    }

    return pagebuf;
}
#endif
