
////////////////////////////////////////////////////////////////////////
//                          WRAPPERS & ALIASES
/////////////////////////////////////////////////////////////////////////

#define vncserver sys "vncserver -localhost" _
#define prootdistro sys "proot-distro login archlinux" _
#define tmux sys "tmux" _
#define ls sys "ls -hAltr" _

void micro(char const *path)
{
	char buf[512];
	snprintf(buf, 512, "micro %s", path);
	system(buf);
	// TODO: undefined escape rules in param strings
}

#define edit micro (
#define _ ) ;
#define sys system (


void mkdir(char *path)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "mkdir %s", path);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define mkdir mkdir (

void mv(char *from, char *to)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "mv %s %s", from, to);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define mv mv (

void cp(char *from, char *to)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "cp %s %s", from, to);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define cp cp (

void rm(char *filename)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "rm %s", filename);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define rm rm (

void cat(char *filename)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "cat %s", filename);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define cat cat (

void touch(char *s)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "touch %s", s);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define touch touch (

void diff(char *from, char *to)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "diff %s %s", from, to);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define diff diff (


////////////////////////////////////////////////////////////////////////
//                          ADDITIONAL COMMANDS
/////////////////////////////////////////////////////////////////////////

#define tmuxhelp printf("ctrl+b+\" \nctrl+b+%%\nctrl+b meta+arrow\n");
#define mainh sys "micro /data/data/com.termux/files/home/prj/bytesh/run/main.h" _


void editcompiler()
{
	system("micro /data/data/com.termux/files/home/prj/bytesh/main.c");
    system("gcc   /data/data/com.termux/files/home/prj/bytesh/main.c \
               -o /data/data/com.termux/files/home/prj/bytesh/a.out");
	exit(0);
}
#define editcompiler editcompiler();

void echosys(char const *cmd)
{
    printf("\n[auto]\n");
	printf("$ %s\n\n", cmd);
	system(cmd);
}
#define echosys echosys (

void gitupdate() {
	    sys "git add *" _
	    sys "git add */*" _
	    sys "git commit -m untitled" _
	echosys "git status" _
	//echosys "git log" _
}
#define gitupdate gitupdate();

void man(char *topic) {
	if (0//!strcmp(topic, "fopen")
	//|| (!strcmp(topic, "fdopen"))
	|| (!strcmp(topic, "freopen")))
	{
		printf("#include <stdio.h>\n");
		printf("FILE *freopen(char *path, char *mode, FILE *f);\n");
		printf("\n");
		printf("The freopen() function opens the file whose name is\n");
		printf("the string pointed to by `path` and associates the\n");
		printf("stream pointed to by `f` with it. The original\n");
		printf("stream (if it exists) is closed.\n");
		printf("\n");
		printf("On failure, NULL is returend and `errno` is set to\n");
		printf("indicate the error.\n");
	
	}
	else if (!strcmp(topic, "memcmov")) 
	{
		printf("NAME\n");
		printf("       memcmov - move memory area\n");
		printf("\n");
		printf("LIBRARY\n");
		printf("       Extended Standard C library\n");
		printf("\n");
		printf("SYNOPSIS\n");
		printf("       #include <stringext.h>\n");
		printf("\n");
		printf("       void *memcmov(void dst[.n], \n");
		printf("                     void const src[.n], int c,\n");
		printf("                     size_t n);\n");
		printf("\n");
		printf("DESCRIPTION\n");
		printf("       The memcmov() function copies no more than\n");
		printf("       `n` bytes from memory area `src` to memory\n");
		printf("       area `dst`, stopping when the character\n");
		printf("       `c` is found (`c` is copied).\n");
		printf("\n");
		printf("       The memory areas may overlap.\n");
		printf("\n");
		printf("RETURN VALUE\n");
		printf("       The memcmov() function returns a pointer to\n");
		printf("       the next character in `dst` after `c`, or\n");
		printf("       NULL if `c` was not found in the first `n`\n");
		printf("       characters of `src`.\n");
		printf("\n");
	}
	if (!strcmp(topic, "fgets"))
	{
		printf("NAME\n");
		printf("       fgets - input of strings\n");
		printf("\n");
		printf("LIBRARY\n");
		printf("       Standard C library\n");
		printf("\n");
		printf("SYNOPSIS\n");
		printf("       #include <stdio.h>\n");
		printf("\n");
		printf("       char *fgets(char s[.n], int n, FILE *f)\n");
		printf("\n");
		printf("DESCRIPTION\n");
		printf("       fgets() reads in at most one less than\n");
		printf("       `size` characters from `f` and stores them\n");
		printf("       into the buffer pointed to by `s`. Reading\n");
		printf("       stops after an EOF or a newline. If a new-\n");
		printf("       line is read, it is stored into the buffer.\n");
		printf("       A terminating null byte ('\\0') is stored\n");
		printf("       after the last character in the buffer.\n");
		printf("       \n");
		printf("RETURN VALUE\n");
		printf("       fgets() returns `s` on success, and NULL on\n");
		printf("       error or when end of file occurs while no\n");
		printf("       characters have been read.\n");
		printf("       \n");
		printf("       \n");
		printf("       \n");
		printf("       \n");
		printf("       \n");


	}
	else
	{
		char cmd[NBUF];
		snprintf(cmd, NBUF, "man %s", topic);
		system(cmd);
	}
}
#define man man (



