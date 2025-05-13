#ifndef RUN_CNSLUTIL_H_INCLUDED
#define RUN_CNSLUTIL_H_INCLUDED

#include "main.h"

////////////////////////////////////////////////////////////////////////
//                          WRAPPERS & ALIASES
/////////////////////////////////////////////////////////////////////////
#define _ ) ;
#define sys system (
#define pfs printf("%s",
#define vncserver sh, "vncserver -localhost", endsh
#define prootdistro sh, "proot-distro login archlinux", endsh
#define tmux sh, "tmux", endsh
#define ls sh, "ls -hAltr", endsh

void syssleep(int ignore, char const *time, char *ignore_)
{
	linebuf_t buf;
	snprintf(buf, sizeof(buf), "sleep %s", time);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define sleep syssleep ( 0

void micro(int ignore, char const *path, char *ignore_)
{
	char buf[512];
	snprintf(buf, 512, "micro %s", path);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define edit micro ( 0

void tputcup(int ignore, int col, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "tput cup %d 0", col);
	system(buf);
}
#define tputcup tputcup ( 0

#define tputed sh, "tput ed", endsh

void mkdir(int ignore, char *path, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "mkdir %s", path);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define mkdir mkdir ( 0

void mv(int ignore, char *from, char *to, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "mv %s %s", from, to);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define mv mv ( 0

void cp(int ignore, char *from, char *to, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "cp %s %s", from, to);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define cp cp ( 0

void rm(int ignore, char *filename, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "rm %s", filename);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define rm rm ( 0

void cat(int ignore, char *filename, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "cat %s", filename);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define cat cat ( 0

void touch(int ignore, char *s, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "touch %s", s);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define touch touch ( 0

void diff(int ignore, char *from, char *to, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "diff %s %s", from, to);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define diff diff ( 0


////////////////////////////////////////////////////////////////////////
//                          ADDITIONAL COMMANDS
/////////////////////////////////////////////////////////////////////////

//#include "prop.h"

void prop(char *filename, char *identget, char *identset)
{
	char headerpath[NBUF] = "";
	strcat(headerpath, ROOT);
	strcat(headerpath, "/run/prop.h");

	char def[NBUF * 64];
	strcat(def, "char * ");
	strcat(def,        identget);
	strcat(def,                "() {\n");
	strcat(def, "    char *path = \"");
	strcat(def,                     ROOT);
	strcat(def,                        "/run/prop/");
	strcat(def,                                   filename);
	strcat(def,                                           "\";\n");
	strcat(def, "    return loads(path);\n");
	strcat(def, "\n");
	strcat(def, "}\n");
	strcat(def, "\n");
	strcat(def, "void \n");
	strcat(def,       identset);
	strcat(def,              "(char *val) {\n");
	strcat(def, "    char *path = \"");
	strcat(def,                     ROOT);
	strcat(def,                        "/run/prop/");
	strcat(def,                                   filename);
	strcat(def,                                           "\";\n");
	strcat(def, "    fputsclose(val, fopen(path, \"w\"));\n");
	strcat(def, "}\n");

	fputsclose(def, fopen(headerpath, "a"));
}
#define prop prop (

#include "quickdef.h"

void quickdef()
{
    char def[NBUF];
    printf(".c (quickdef) $ ");
    fgets(def, NBUF, stdin);
	char path[NBUF];
	snprintf(path, NBUF, "%s/run/cnslutil.h", ROOT);
    char defb[strlen(def) + 2];
    strcpy(defb, def);
    defb[strlen(def)] = '\n';
    defb[strlen(def) + 1] = 0;
	fputsclose(defb, fopen(path, "a"));
}
#define quickdef quickdef()

void programm()
{
	linebuf_t path = "";
	snprintf(path, sizeof(linebuf_t), "%s%s", ROOT, "/run/programm.txt");
	edit, path, endsh;
}
#define programm programm()

#define tmuxh printf("ctrl+b+\" \nctrl+b+%%\nctrl+b meta+arrow\n");

#define mainh     (sh, mlinebufprintf("micro %s/%s", ROOT, "run/main.h"), endsh)
#define cnslutilh (sh, mlinebufprintf("micro %s/%s", ROOT, "run/cnslutil.h"), endsh)

void editcompiler()
{
	system("micro /data/data/com.termux/files/home/prj/bytesh/main.c");
    system("gcc   /data/data/com.termux/files/home/prj/bytesh/main.c \
               -o /data/data/com.termux/files/home/prj/bytesh/a.out");
	exit(0);
}
#define editcompiler editcompiler()

void echosys(char const *cmd)
{
    printf("\n[auto]\n");
	printf("$ %s\n\n", cmd);
	system(cmd);
}
#define echosys echosys (

void gitupdate() {
	    sh, "git add *", endsh;
	    sh, "git add */*", endsh;
	    sh, "git commit -m untitled", endsh;
	    sh, "git push", endsh;
	    sh, "git status", endsh;
	    sh, "echo git status", endsh;
	//echosys "git log" _
}
#define gitupdate gitupdate()

void man(int ignore, char *topic, char *ignore_) {
	if (!strcmp(topic, "freopen"))
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
	else if (!strcmp(topic, "fgets"))
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
#define man man ( 0


#endif

// quickdef

#define clear sys "clear" _
#define tputsc sys "tput sc" _
#define tputrc sys "tput rc" _
#define repeat(n) for (int i = 0; i < n; ++i)


#define longtext repeat(100) {pfs "hello, world" _ ln}

#define mpv(s) sys \
    (\
        snprintf(\
            mallocadd(sizeof(linebuf_t)), \
            sizeof(linebuf_t), \
            "mpv %s", s\
        ),\
        lastmalloc\
    ) _

#define quickdefh edit ROOTC("/run/quickdef.h") _

#define storagepath "/storage/emulated/0/"

#define s "%s"



#define lnsfn(a, b) sys (mallocadd(sizeof(linebuf_t)), snprintf(lastmalloc, sizeof(linebuf_t), "ln -s %s %s", a, b), lastmalloc) _

#define lns lnsfn (


#define stdioexth (edit, mlinebufprintf("ROOT/%s", "/run/stdioext.h", endsh)

#define psefgrep (sh, mlinebufprintf("ps -ef | grep %s", term), endsh)

#define termux11 (sh, "termux-x11 :1 -xstartup \"dbus-launch --exit-with-session xfce4-session\"", endsh)

#define gpgencrypt sh, "gpg -a -c %s"

