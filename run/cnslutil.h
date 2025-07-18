#ifndef RUN_CNSLUTIL_H_INCLUDED
#define RUN_CNSLUTIL_H_INCLUDED

#include "main.h"

////////////////////////////////////////////////////////////////////////
//                          WRAPPERS & ALIASES
/////////////////////////////////////////////////////////////////////////

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
#define ROOTCLS ROOTC("/run/cnslutil/ls.txt")
#define ls  sh, mf("ls -hAl  %%s > %s ; micro %s", ROOTCLS, ROOTCLS)
#define lst sh, mf("ls -hAlt %%s > %s ; micro %s", ROOTCLS, ROOTCLS)
#define lsS sh, mf("ls -hAlS %%s > %s ; micro %s", ROOTCLS, ROOTCLS)
#define lsc  ls, ".", endsh
#define lsct lst, ".", endsh
#define lscS lsS, ".", endsh
#define lscgrep sh, "ls -hAl . | grep %s"
#define lsgrep sh, "ls -hAl %s | grep %s"

#define history cmdlog

#define errfixdone SYSTOBOOL(bak, ROOTC("run"), endsh) && mv, ROOTC("run.err"), ROOTC("run"), endsh;

extern char *rootworkdir;

void micro_(int ignore, char const *path, char *ignore_);
#define edit micro_ ( 0


#define cmdlogedit edit, ROOTC("/run/log.txt"), endsh

void cmdlog_();
#define cmdlog cmdlog_()
#define cmdlogh printf("See also: cmdloggrep, cmdloghead(int end), cmdlogat(int i, linebuf_t *buf)")

void cmdloggrep_(char *mask);

void cmdloghead(int end);

#define cmdlogregionh \
     printf("%s\n", "cmdlogregion(int from, int to, char buf[linebuf_tn * (to - from)])");

void cmdlogregion(int from, int to, char *buf);

void cmdinsert(char *cmd);

#define cmdinsertlogat(addr) cmdinsertlogregion(addr, addr + 1)

void cmdinsertlogregion(int from, int to);

void syssleep(int ignore, char const *time, char *ignore_);
#define sleep syssleep ( 0

void tputcup(int ignore, int col, char *ignore_);
#define tputcup tputcup ( 0

#define tputed sh, "tput ed", endsh

void mkdir_(int ignore, char *path, char *ignore_);
#define mkdir mkdir_ ( 0

void mkdirp_(int ignore, char *path, char *ignore_);
#define mkdirp mkdirp_ ( 0

int mv_(int ignore, char *from, char *to, char *ignore_);
#define mv mv_ ( 0

#define mvf sh, "mv -f %s %s"
#define rmf sh, "rm -f %s %s"

void cp_(int ignore, char *from, char *to, char *ignore_);
#define cp cp_ ( 0

void rm_(int ignore, char *filename, char *ignore_);
#define rm rm_ ( 0

void cat_(int ignore, char *filename, char *ignore_);
#define cat cat_ ( 0

void touch_(int ignore, char *sz, char *ignore_);
#define touch touch_ ( 0

void diff_(int ignore, char *from, char *to, char *ignore_);
#define diff diff_ ( 0

void hcreate(char *name);

# define BACKSLASH ((char) 92)

#define xyzhadd hadd
#define hadd(namepath)   haddfn(namepath, 0)
#define haddfn(namepath, ident) hadditem(namepath, ident, 0)

void hadditem(char *namepath, char *ident, int preprocessor);

#define cnslutilhadd xyzhadd("cnslutil")
#define cnslutilhaddfn(ident) haddfn("cnslutil", ident)
#define cnslutilhadddef(ident) hadditem("cnslutil", ident, 1)
#define tmphadd xyzhadd("tmp")
#define tmphaddfn(ident) haddfn("tmp", ident)
#define tmphadddef(ident) hadditem("tmp", ident, 1)

void programm();
#define programm programm()

#define tmuxh printf("ctrl+b+\" \nctrl+b+%%\nctrl+b meta+arrow\n");

#define mainh     (sh, mlinebufprintf("micro %s/%s", ROOT, "run/main.h"), endsh)
#define cnslutilh (sh, mlinebufprintf("micro %s/%s", ROOT, "run/cnslutil.h"), endsh)

# define compilerh edit, ROOTC("main.c"), endsh;

void echosys(char const *cmd);
#define echosys echosys (

void gitupdate();
#define gitupdate gitupdate()

# define PIPES "|"

void man(int ignore, char *topic, char *ignore_) ;
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

void du(char *, int depth, char *);
#define du du (

int yays(int ignore, char *x, char *ignores);
#define yays yays ( 0

#define pacmansyyu sh, "sudo pacman -Syyu", endsh
#define pacmansyu  sh, "sudo pacman -Syu",  endsh
#define pacmansyy  sh, "sudo pacman -Syy",  endsh
#define pacmansy   sh, "sudo pacman -Sy",   endsh

int pacmans(int ignore, char *x, char *ignores);
#define pacmans pacmans ( 0

int pacmanss_(int ignore, char *x, char *ignores);
#define pacmanss pacmanss_ ( 0

int pacmanqi(int ignore, char *x, char *ignores);
#define pacmanqi pacmanqi ( 0

#define rmr sh, "rm -r %s"

#define cpr sh, "cp -r %s %s"

#define ping sh, "ping %s"

int pacmanql(int ignore, char *x, char *ignores);
#define pacmanql pacmanql ( 0

#define libreoffice sh, "%s libreoffice %s %s", DISPLAYCONFIG, QUIET, BG, endsh

int pacmanr(int ignore, char *x, char *ignores);
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

int yayss_(int ignore, char *pkg, char *ignores);
#define yayss yayss_ ( 0

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


#define ENDBLOCK

# define bakpre(f) mkdir, "-p .bak", endsh; mv, f, ".bak", endsh;

void bak_(char *a, char *f, char *b);
#define bak bak_ ( ""

# define meld sh, "%s meld %s %s", DISPLAYCONFIG, QUIET, BG, endsh


# define stringexth edit, ROOTC("/run/stringext.h"), endsh



#include ".//cnslutil/curl.h"

# define mainsysh edit, ROOTC("/run/mainsys.h"), endsh

# define microsyntax edit, "/data/data/com.termux/files/home/.config/micro/syntax/cext.yaml", endsh

#define asciih printf("%s", "Found in: $ cnslutilh")
#define ascii printallascii




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

#define vncserverconfigh printf("%s", "Found in: $ cnslutilh\n")
#define vncserverconfig edit, "/home/mbrandt/.config/tigervnc/config", endsh


#include ".//mtnc.h"
#include ".//mntc.h"
#include ".//tmp/termiostest.h"
#define exechh printf("%s", "Found in: $ cnslutilh\n")
#define exech man, "exec", endsh

#include "scanfs.h"
#define stdlibexth_addkeywordh printf("%s", "Found in: $ cnslutilh\n")

#define cnsllinedelh printf("%s", "Found in: $ cnslutilh\n")
#define cnsllinedel \
	rep iff unbufreadc(STDIN_FILENO) == (int) 'c'      \
	    thn {printf("%s", "\033[2K\033[T"); fflush(stdout);}        \
	    els break;
	
#define cnsllinedeldown(n) \
	for range(0, n)\
	stm printf("%s", "\033[2K");


#define dbus_daemon_sessionh printf("%s", "Found in: $ cnslutilh\n")
#define dbus_daemon_session \
    sh, "dbus-daemon --session --print-address > %s %s", \
        ROOTC("/run/cnslutil/dbus_daemon_session_address.txt"), BG, endsh

#define dbus_session_bus_address_config \
    mf("%s=\"%s\"", "DBUS_SESSION_BUS_ADDRESS", dbus_session_bus_address)


#define edithh printf("%s", "Found in: $ cnslutilh\n")
#define edith edit, ROOTC("/run/cnslutil/edith.md"), endsh


#define lnhh printf("%s", "Found in: $ cnslutilh\n")
#define lnh man, "ln", endsh


#define microh printf("%s", "Found in: $ cnslutilh\n")


#define diffwh printf("%s", "Found in: $ cnslutilh\n")
#define diffw sh, "diff -w %s %s"


#define TERMUX_HOMEh printf("%s", "Found in: $ cnslutilh\n")
#define TERMUX_HOME "/data/data/com.termux/files/home/"


#define tarxvfh printf("%s", "Found in: $ cnslutilh\n")
#define tarxvf sh, "tar xvf %s"


#define pacmanyayssh printf("%s", "Found in: $ cnslutilh\n")

int pacmanyayss(char *ignore, char *pkg, char *ignore2);

#define pacmanyayss pacmanyayss ( 0
#define gitcloneh printf("%s", "Found in: $ cnslutilh\n")
//#define ROOTCGITCLONE ROOTC("/run/cnslutil/gitclone.txt")
//#define gitclone sh, mf("git clone %%s > %s 2>&1 & && %s" \
//                        "echo 'Command started in background, output piped to %s.'",
//                        ROOTCGITCLONE, ROOTCGITCLONE)


#define PREPATHh printf("%s", "Found in: $ cnslutilh\n")
#define PREPATH sh, "export PATH=\"%s:$PATH\""


