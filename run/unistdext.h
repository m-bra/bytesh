#define unistdexth edit, ROOTC("/run/unistdext.h"), endsh
#define unistdexthadd hadd("unistdext")
#define unistdexthaddfn(ident) haddfn("unistdext", ident)
#define unistdexthadddef(ident) hadditem("unistdext", ident, 1)


#define readch printf("%s", "Found in: $ unistdexth\n")
int readc(int fd)
{
	char buf;
iff read(fd, &buf, 1)
thn return buf;
els return EOF;		
}
