#include "main.h"

#ifndef USERINTERFACEHINCLUDED
#define USERINTERFACEHINCLUDED
#define userinterfaceh edit, ROOTC("/run/userinterface.h"), endsh
#define userinterfacec edit, ROOTC("/run/userinterface.c"), endsh
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

SECTION TEXT

SECTION DATA

extern struct termios uirestoreval;
char *mgetline(char *beginlinefmt);

struct termios uiunbuffered();

void uibuffered();

void uirestore(struct termios old_tio);

SECTION TEXT

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

#define mgetescline mgetline

SECTION DATA

void uiexample_rendered(int i);

void uitest();

int unbufreadc(int fd);


#endif
