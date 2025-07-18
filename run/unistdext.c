#include "main.h"

int readc(int fd)
{
	char buf;
iff read(fd, &buf, 1)
thn return buf;
els return EOF;		
}
