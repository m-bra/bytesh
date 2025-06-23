#define readconfh edit, ROOTC("/run/readconf.h"), endsh
#define readconfhadd hadd("readconf")
#define readconfhaddfn(ident) haddfn("readconf", ident)
#define readconfhadddef(ident) hadditem("readconf", ident, 1)

/*
int fskipwh(FILE *f)
{
	rep {
	
	}
}

int readconf() {
	FILE *f = fopen(pacmanssqemutxt, "r");\
	rep {\
	    int r = fskipwh(f);\
	    r = r || fskiphash(f);\
	    int c;\
	iff (c = fgetc(f)) == EOF
	thn break;
	    printf("%c", (char) c);\
	iff r \
	thn printf(" ");\
	}\
	return 1;\
	\
err: 
    printf("Error at main\n");\
    return 0;
}

*/
