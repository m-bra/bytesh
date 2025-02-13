#define MAIN_BEGIN runbatch();
#define MAIN_END mvbatch(); statusprint(syssh);

#warning system() does not wait for command to exit!

#define NBUF 512

#define ROOT "/data/data/com.termux/files/home/prj/bytesh/"
#define ROOTLEN strlen(ROOT)

#include "stdlib.h"
#include "stdlibext.h"
#include "unistd.h"
#include "string.h"
#include "stringext.h"
#include "stringutil.h"
#include "stdioext.h"

#include "cnslutil.h"
#include "misc.h"

//#include "todo.h"


void statusprint(int issyssh)
{
	char cwd[NBUF]; getcwd(cwd, NBUF);
    if (1)
    {
    	printf("\n[%s]\n",  cwd);
    	if (issyssh) {
    		printf(".sh (priv) $ ");
    	} else {
    		printf(".c (priv) $ ");
    	}
    }
}

void test()
{
}
