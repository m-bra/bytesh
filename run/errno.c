#include <errno.h>

void seterrno(int e)
{
	errno = e;
}

int geterrno()
{
	return errno;
}
