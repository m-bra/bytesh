#ifndef RUN_CNSLUTIL_H_INCLUDED
#define RUN_CNSLUTIL_H_INCLUDED

#include "main.h"

////////////////////////////////////////////////////////////////////////
//                          WRAPPERS & ALIASES
/////////////////////////////////////////////////////////////////////////
#define _ ) ;
#define sys system (
#define pfs printf("%s",

#define QUIET "> /dev/null 2>&1"
#define ROOTLOG(name) mf("> /root/%s.log 2>&1", name)
#define BG "&"
#define DISPLAYN 4
#define DISPLAYCONFIG mf("DISPLAY=:%d", DISPLAYN)

#define LOGVNCSERVER ROOTLOG(mf("vncserver.%d", DISPLAYN))
#define vncserver sh, "vncserver :%d %s %s", \
                      DISPLAYN, LOGVNCSERVER, BG, endsh

#define prootdistrou(PROOTUSER) sh, "proot-distro login archlinux --user %s", PROOTUSER, endsh
#define prootdistro prootdistrou("mbrandt")

#define tmux sh, "tmux", endsh
#define ls sh, "ls -hAl %s"
#define lsc ls, ".", endsh
#define lscgrep sh, "ls -hAl . | grep %s"
#define lsgrep sh, "ls -hAl %s | grep %s"

#define history cmdlog

#define errfixdone rmr, mf("%s/%s", ROOT, "/run"), endsh; mv, mf("%s/%s", ROOT, "/run.err"), mf("%s/%s", ROOT, "/run"), endsh;

extern char *rootworkdir;

void micro(int ignore, char const *path, char *ignore_)
{
	char buf[512];
	snprintf(buf, 512, "micro %s", path);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define edit micro ( 0


#define cmdlogedit edit, ROOTC("/run/log.txt"), endsh

void cmdlog()
{
	FILE *f = fopen(mf("%s/%s", rootworkdir, "/log.txt"), "r");
	linebuf_t buf;
	int linen = -1;
	while loop {
		linen+= 1;
		if (!fgets((char *) buf, linebuf_tn, f))
			break;
		printf("0x%05X .. $ %s", linen, (char *) buf);
		//printf("%s", (char *)buf);
	}

	fclose(f);
}
#define cmdlog cmdlog()
#define cmdlogh printf("See also: cmdloggrep, cmdloghead(int end), cmdlogat(int i, linebuf_t *buf)")

void cmdloggrep(char *mask)
{
	FILE *f = fopen(mf("%s/%s", rootworkdir, "/log.txt"), "r");
	linebuf_t buf[4];
	int linen = -1;
	while loop {
		linen+= 1;
		if (!fgets((char *) buf, 4 * linebuf_tn, f))
			break;
		if (strstr((char *) buf, mask))
			printf("0x%05X .. $ %s", linen, (char *)buf);
	}

	fclose(f);
}

void cmdloghead(int end)
{
	FILE *f = fopen(mf("%s/%s", rootworkdir, "/log.txt"), "r");
	linebuf_t buf;
	int linen = -1;
	while loop {
		linen+= 1;
		if (!fgets((char *) buf, linebuf_tn, f))
			break;
		if (linen < end)
			printf("0x%05X .. $ %s", linen, (char *)buf);
	}

	fclose(f);
}

#define cmdlogregionh \
     printf("%s\n", "cmdlogregion(int from, int to, char buf[linebuf_tn * (to - from)])");
loctag
void cmdlogregion(int from, int to, char *buf)
{
	char *p = buf;
	for (int i = from; i < to; ++i) {
		cmdlogat(i, (linebuf_t *) p);
		p += strlen(p);
	}	
}

#define l    cmdinsertlogregion(cmdlogn() - 1, cmdlogn() - 0);
#define ll   cmdinsertlogregion(cmdlogn() - 2, cmdlogn() - 1);
#define lll  cmdinsertlogregion(cmdlogn() - 3, cmdlogn() - 2);

void cmdinsert(char *cmd)
{
	fputsclose(cmd, fopen(ROOTC("/insert.c"), "a"));
}

#define cmdinsertlogat(addr) cmdinsertlogregion(addr, addr + 1)

void cmdinsertlogregion(int from, int to)
{
	int nbuf = (to - from) * linebuf_tn;
	char *buf = mallocadd(nbuf);
	cmdlogregion(from, to, buf);

	char *filename = ROOTC("/run/cnslutil/cmdinsertlogregion.txt");
	fputsclose(buf, fopen(filename, "w"));
	edit, filename, endsh;
	char *nextbuf = mallocadd(32 * pagebuf_tn);
	fgetallsclose(nextbuf, 32 * pagebuf_tn, fopen(filename, "r"));
	cmdinsert(nextbuf);
}

void syssleep(int ignore, char const *time, char *ignore_)
{
	linebuf_t buf;
	snprintf(buf, sizeof(buf), "sleep %s", time);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define sleep syssleep ( 0

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

void mkdirp(int ignore, char *path, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "mkdir -p %s", path);
	system(buf);
	// TODO: undefined escape rules in param strings
}
#define mkdirp mkdirp ( 0

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

void touch(int ignore, char *sz, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "touch %s", sz);
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


loctag
void hcreate(char *name)
{
	char *lastslash = strrstr(name, "/");
	char *nameleaf = lastslash;
	if ( nameleaf) nameleaf += 1;
	if (!nameleaf) nameleaf = name;
	if (!lastslash) lastslash = name;

	char parent [linebuf_tn];
iff (lastslash - name) + 1 > linebuf_tn
thn goto err;
	strncpy(parent, name, lastslash - name);
	parent[lastslash - name] = 0;

	char NL = '\n';

	mkdirp, mf("%s/%s/%s", ROOT, "run", parent), endsh;
	
	fputsclose(
    	mf(
    		//"#ifndef HEADERGUARD_%s%c"
    		//"#define HEADERGUARD_%s%c"
			"#define %sh edit, ROOTC(%c/run/%s.h%c), endsh%c"
			"#define %shadd hadd(%c%s%c)%c"
			"#define %shaddfn(ident) haddfn(%c%s%c, ident)%c"
			"#define %shadddef(ident) hadditem(%c%s%c, ident, 1)%c"
    		"%c"
    		"%c",
    		//"#endif  HEADERGUARD_%s%c",
    		//nameleaf, NL, 
    		//nameleaf, NL, 
    		nameleaf, '"', name, '"', NL,
    		nameleaf, '"', name, '"', NL,
    		nameleaf, '"', name, '"', NL,
    		nameleaf, '"', name, '"', NL,
    		NL, 
    		NL 
    		//nameleaf, NL
    	),
		fopen(mf("%s/%s/%s.%s", ROOT, "run", name, "h"), "a")	
	);
	fputsclose(
		mf(
			"#include %c%s/%s/%s.h%c%c",
			'"', ".", "", name, '"', NL
		),
		fopen(mf("%s/run/%s", ROOT, "cnslutil.h"), "a")
	);
	return;

err:
	printf("Error at %s:%d%c", __FILE__, __LINE__, '\n');
	return;
}

# define BACKSLASH ((char) 92)

#define xyzhadd hadd
#define hadd(namepath)   haddfn(namepath, 0)
#define haddfn(namepath, ident) hadditem(namepath, ident, 0)
void hadditem(char *namepath, char *ident, int preprocessor)
{
	char *fnct = ident;
	
	char *name = strrstr(namepath, "/");
	if ( name) name += 1;
	if (!name) name = namepath;
	
	char *cmd = mf("%sh", name);
	char *filename = mf("%s.h", namepath);
	
	char *prompt = mf("%s%sadd%s $ ", mf(PROMPT, 0xFFFF, ""), cmd, fnct ? (preprocessor ? "def" : "fn") : "");
	printf("%s", prompt);
	fflush(stdout);
		
	char space[] = "                                 ";
	space[strlen(prompt) - 5] = 0;
	char *szdef = mgetescline(mf("%s%%02d $ ", space));
    
	char path[NBUF];
	snprintf(path, NBUF, "%s/run/%s", ROOT, filename);

    char szdefb[strlen(szdef) + 2];
    strcpy(szdefb, szdef);
    szdefb[strlen(szdef)] = '\n';
    szdefb[strlen(szdef) + 1] = 0;

    char *NLS = "\n";

	FILE *f = fopen(path, "a");
	fnct&&fputs(mf("#define %sh printf(%c%%s%c, %cFound in: $ %s%cn%c)%c", 
	             fnct, '"', '"', '"', cmd, BACKSLASH, '"', *NLS), f);

	int pp =  preprocessor;
	int np = !preprocessor;
	np&&fnct&&fputs(mf("void %s()%c", ident, *NLS), f);
	np&&fnct&&fputs(   mf("{%c", *NLS),      f);
	np&&     fputs(       szdefb, f);
	np&&fnct&&fputs(   mf("}%c", *NLS),      f);
	pp&&fnct&&fputs(mf("#define %s %s%c", ident, szdefb, *NLS), f);
}

#define cnslutilhadd xyzhadd("cnslutil")
#define cnslutilhaddfn(ident) haddfn("cnslutil", ident)
#define cnslutilhadddef(ident) hadditem("cnslutil", ident, 1)
#define tmphadd xyzhadd("tmp")
#define tmphaddfn(ident) haddfn("tmp", ident)
#define tmphadddef(ident) hadditem("tmp", ident, 1)

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

# define compilerh edit, ROOTC("main.c"), endsh;

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
	    //sh, "git status", endsh;
	    //sh, "echo git status", endsh;
	//echosys "git log" _
}
#define gitupdate gitupdate()

# define PIPES "|"

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
		printf("       fgets() reads in less than\n");
		printf("       `size` characters from `f` and stores them\n");
		printf("       into the buffer pointed to by `s`.\n");
		printf("       Stops after an EOF or a newline.\n");
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
	els blk
	stm char *filename = mf("%s%s%s", ROOTC("/run/cnslutil/man/"), topic, ".txt");
	iff access(filename, F_OK) != 0
	thn sh, "man %s | col -b > %s", topic, filename, endsh;
	stm edit, filename, endsh;
	blk_end
}
#define man man ( 0


#endif

// quickdef

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

#define lnsfn(a, b) sys (mallocadd(sizeof(linebuf_t)), snprintf(lastmalloc, sizeof(linebuf_t), "ln -s %s %s", a, b), lastmalloc) _

#define lns lnsfn (


#define psgrep printf("UID        PID  PPID  C STIME TTY          TIME CMD\n"), sh, "ps -ef --forest | grep %s"
#define ps sh, "ps -ef --forest", endsh

#define termux11 (sh, "termux-x11 :1 -xstartup \"dbus-launch --exit-with-session xfce4-session\"", endsh)

#define gpgencrypt sh, "gpg -a -c %s"
#define gpgdecrypt sh, "gpg -a -d %s"

#define date sh, "date", endsh

void du(int depth) {sh, "du -h -d %d", depth, endsh;}


int yays(int ignore, char *x, char *ignores)
{
	return sh, "yay -S %s", x, endsh;
}
#define yays yays ( 0

#define pacmansyyu sh, "sudo pacman -Syyu", endsh
#define pacmansyu  sh, "sudo pacman -Syu",  endsh
#define pacmansyy  sh, "sudo pacman -Syy",  endsh
#define pacmansy   sh, "sudo pacman -Sy",   endsh

int pacmans(int ignore, char *x, char *ignores)
{
	return sh, "sudo pacman -S %s", x, endsh;
}
#define pacmans pacmans ( 0

int pacmanss(int ignore, char *x, char *ignores)
{
	return sh, "pacman -Ss %s > /tmp/pacmanss.txt", x, endsh;
	edit, "/tmp/pacmanss.txt", endsh;
}
#define pacmanss pacmanss ( 0

int pacmanqi(int ignore, char *x, char *ignores)
{
	return sh, "pacman -Qi %s", x, endsh;
}
#define pacmanqi pacmanqi ( 0

#define rmr sh, "rm -r %s"

#define cpr sh, "cp -r %s %s"

#define ping sh, "ping %s"

int pacmanql(int ignore, char *x, char *ignores)
{
	return sh, "pacman -Ql %s", x, endsh;
}
#define pacmanql pacmanql ( 0

#define libreoffice sh, "%s libreoffice %s %s", DISPLAYCONFIG, QUIET, BG, endsh

int pacmanr(int ignore, char *x, char *ignores)
{
	return sh, "sudo pacman -R %s", x, endsh;
}
#define pacmanr pacmanr ( 0

 # define which sh, "which %s"

//# define kill sh, "kill -sigkill %s"

# define pwd sh, "pwd", endsh

# define aptinstall sh, "apt install %s"

# define stat sh, "stat %s"

# define whoami sh, "whoami", endsh

#define firefox sh, "%s firefox -P default-release %s %s", DISPLAYCONFIG, QUIET, BG, endsh

# define qutebrowser sh, "%s qutebrowser %s %s", DISPLAYCONFIG, QUIET, BG, endsh

# define dynalist sh, "%s firefox -P dynalist --new-tab 'https://dynalist.io/' %s %s", DISPLAYCONFIG, QUIET, BG, endsh

# define urxvt sh, "%s urxvt -e bytesh %s %s", DISPLAYCONFIG, QUIET, BG, endsh

# define killh printf(s, "kill(pid_t pid, int sig)");ln;



# define xterm sh, "%s xterm %s %s", DISPLAYCONFIG, QUIET, BG, endsh

# define sigterm(pid) kill(pid, SIGTERM);
# define sigkill(pid) kill(pid, SIGKILL);
# define suroot sh, "su -c bytesh - root", endsh



# define psgrepvnc psgrep, "vnc", endsh

# define top sh, "top", endsh

# define chmodx sh, "chmod +x %s"

# define memstress sh, "stress --timeout 6 -m 1 --vm-keep --vm-bytes %s"

# define memstressloop \
  printf("2250M: "); fflush(stdout); memstress, "2250M", endsh;\
  printf("2300M: "); fflush(stdout); memstress, "2300M", endsh;\
  printf("2350M: "); fflush(stdout); memstress, "2350M", endsh;\
  printf("2400M: "); fflush(stdout); memstress, "2400M", endsh;\
  printf("2450M: "); fflush(stdout); memstress, "2450M", endsh;\
  printf("2500M: "); fflush(stdout); memstress, "2500M", endsh;\
  printf("2550M: "); fflush(stdout); memstress, "2550M", endsh;\
  printf("2600M: "); fflush(stdout); memstress, "2600M", endsh;\
  printf("2650M: "); fflush(stdout); memstress, "2650M", endsh;\
  printf("2700M: "); fflush(stdout); memstress, "2700M", endsh;\
  while loop {\
    printf("Enter memory or q.. : ");\
    char *answer = mgetescline("");\
    if (!strncmp(answer, "q", 1)) break;\
    memstress, answer, endsh;\
  }

# define ARCH printf("Lenovo Tab M10: ARMv8 64bit");ln;



# define breakifn(msg) ln; printf(s, msg); if (!strncmp("n", mgetescline(""), 1)) break;
# define breakify(msg) ln; printf(s, msg); if (!strncmp("y", mgetescline(""), 1)) break;
# define breakifq(msg) ln; printf(s, msg); if (!strncmp("q", mgetescline(""), 1)) break;
# define breakifqdef breakifq("loop... ")
# define stdioexth edit, mf("%s/%s", ROOT, "/run/stdioext.h"), endsh

# define stdlibexth edit, mf("%s/%s", ROOT, "/run/stdlibext.h"), endsh

# define STRINGIFY(x) #x

# define displaysh(...) sh, "%s %s %s %s", DISPLAYCONFIG, mf(__VA_ARGS__), QUIET, BG, endsh

# define elev \


int yayss(int ignore, char *pkg, char *ignores)
{
	return sh, "yay -Ss %s", pkg, endsh;
}
#define yayss yayss ( 0

# define PIPE |

# define PIPEC '|'

# define program programm

#define gccaout(f) sh, "gcc %s", f, endsh; sh, "./a.out", endsh; rm, "./a.out", endsh

#define ffmpegi sh, "ffmpeg -i %s %s"

#define textstreamanimateh \
  edit, mf("%s/%s", ROOT, "../textstreamanimate/textstreamanimate.h"), endsh;

#define posttsa \
  \
  // sh, "%s firefox -P default-release %s%s %s %s", DISPLAYCONFIG, "file://", ROOTC("../textstreamanimate/main.png"), QUIET, BG, endsh




# define tsah textstreamanimateh



# define wc(f) sh, "wc %s", f, endsh

# define tmph edit, ROOTC("/run/tmp.h"), endsh

# define strncpyh man, "strncpy", endsh



# define NL '\n'
# define NLC NL
# define NLS "\n"

\
void browsertabtitle(char *title) \
{\
  fputsclose(mf("<title> %s </title>", title), fopen(mf("%s%s%s%s", ROOT, "/run/var/browsertabs/", title, ".html"), "w"));\
  printf("%s%s%s%s%s", "file://", ROOT, "/run/var/browsertabs/", title, ".html");
}\


#define ENDBLOCK

# define bakpre(f) mkdir, "-p .bak", endsh; mv, f, ".bak", endsh;

void bak(char *a, char *f, char *b)
{
	(void) a;
	(void) b;
	bakpre(f)
}
#define bak bak ( ""

# define meld sh, "%s meld %s %s", DISPLAYCONFIG, QUIET, BG, endsh


# define stringexth edit, ROOTC("/run/stringext.h"), endsh



#include ".//cnslutil/curl.h"

# define mainsysh edit, ROOTC("/run/mainsys.h"), endsh

# define microsyntax edit, "/data/data/com.termux/files/home/.config/micro/syntax/cext.yaml", endsh

#define asciih printf("%s", "Found in: $ cnslutilh")

void ascii()
{
  for (int i = 0; i < 256; ++i)
    printf("%03d '%c' ", i, (char)i);
  ln;
}





#define prettierh printf("%s", "Found in: $ cnslutilh\n")
#define prettier sh, "prettier -w %s"


#include ".//test444.h"
#include ".//subtest/test333.h"
#include ".//htmlutil.h"
#define i3configh printf("%s", "Found in: $ cnslutilh\n")
#define i3config edit, "$HOME/.config/i3/config", endsh


#define docfrltxth printf("%s", "Found in: $ cnslutilh\n")
#define docfrltxt edit, "/home/mbrandt/doc/frl.a.txt", endsh


#define sigactionhh printf("%s", "Found in: $ cnslutilh\n")
#define sigactionh man, "sigaction", endsh


#define signalhh printf("%s", "Found in: $ cnslutilh\n")
#define signalh man, "signal.h", endsh


#define fgetchh printf("%s", "Found in: $ cnslutilh\n")
#define fgetch man, "fgetc", endsh


#define fsetposhh printf("%s", "Found in: $ cnslutilh\n")
#define fsetposh man, "fsetpos", endsh


#define fgetposhh printf("%s", "Found in: $ cnslutilh\n")
#define fgetposh man, "fsetpos", endsh


#define strlenhh printf("%s", "Found in: $ cnslutilh\n")
#define strlenh man, "strlen", endsh


#define fgetshh printf("%s", "Found in: $ cnslutilh\n")
#define fgetsh man, "fgets", endsh


#include ".//readconf.h"
#define lnshh printf("%s", "Found in: $ cnslutilh\n")
#define lnsh man, "ln", endsh


#define test1234h printf("%s", "Found in: $ cnslutilh\n")
#define test1234 


#define test647h printf("%s", "Found in: $ cnslutilh\n")
#define test647 


#define vncserverconfigh printf("%s", "Found in: $ cnslutilh\n")
#define vncserverconfig edit, "/home/mbrandt/.config/tigervnc/config", endsh


#include ".//mtnc.h"
#include ".//mntc.h"
#include ".//tmp/termiostest.h"
#define exechh printf("%s", "Found in: $ cnslutilh\n")
#define exech man, "exec", endsh

#include "scanfs.h"
#define stdlibexth_addkeywordh printf("%s", "Found in: $ cnslutilh\n")

void stdlibexth_addkeyword()
{
	printf("keyword:\n#define "); char *szkeyword = mgetline("");
	printf("syntax type (statement, type): "); char *sztype = mgetline("");
    char *configfilename = "/data/data/com.termux/files/home/.config/micro/syntax/cext.yaml";
    fputsclose(mf("\n - %s : \"%s\"\n", sztype, szkeyword), fopen(configfilename, "a"));
    printf("#define %s ", szkeyword); char *keywordbody = mgetline("");
    fputsclose(mf("#define %s %s", szkeyword, keywordbody), fopen(ROOTC("/run/stdlibext.h"), "a"));\
}
#define cnsllinedelh printf("%s", "Found in: $ cnslutilh\n")
#define cnsllinedel \
	rep iff unbufreadc(STDIN_FILENO) == (int) 'c'      \
	    thn {printf("%s", "\033[2K\033[T"); fflush(stdout);}        \
	    els break;
	
#define cnsllinedeldown(n) \
	for range(0, n)\
	stm printf("%s", "\033[2K");


