#define test444h edit, ROOTC("/run/test444.h"), endsh
#define test444hadd hadd("test444")
#define test444haddfn(ident) haddfn("test444", ident)
#define test444hadddef(ident) hadditem("test444", ident, 1)


#define test4445h printf("%s", "Found in: $ test444h\n")
#define test4445 printf("success")


