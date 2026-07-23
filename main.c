
#include <sys/wait.h>
#include "run/main.h"

//#include <stdlib.h>
//#include <unistd.h>
//#include <fcntl.h>

#define _XOPEN_SOURCE 600
#include <stdbool.h>
#include <stdint.h>
//#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
//#include <termios.h>
#include <poll.h>

typedef char **ppchar;
typedef char *pchar;

#include "cflags.h"

chr *rootworkdir;
int isfirstcmd;
int main_interactive;

nil loadcwd(char *rootworkdir);

#define maincontext \
    int isfirstcmd; \
    int interactive; \
    int syssh; \
    pchar rootworkdir; \
    int setemptyline; \
    pchar lastline; int lastlinen; \
    pchar linebuf; \
    pchar line; \
    pchar cwd; \
    pchar argcmd; \
                  \
    FILE *srcfile; \

typedef struct {maincontext} maincontext_t;

char *ctxtmwf(malloclist_t *malloclist, maincontext_t *ctxt, char *path)
{
    return mlinebufprintf("%s/%s", ctxt->rootworkdir, path);
}
#define ctxtmwf(path) ctxtmwf(malloclist, ctxt, path)
#define ctxtmrootworkdirfile ctxtmwf

nil mainprintsubmainbegin(maincontext_t *ctxt);
nil maincdcase(maincontext_t *ctxt);
nil mainremoveunescnl(char *line);
nil mainprintsubmainend(maincontext_t *ctxt);
chr *whitestatus();
chr *trimmatchingend(char *target, char ch);

#define printfflush(...) {printf(__VA_ARGS__); fflush(getstdout());}

#define ignore

//EVALECHO
//(

int innermain(maincontext_t *ctxt)
blk 
int nextbackup = 10;
stm dup2(STDOUT_FILENO, STDERR_FILENO);

stm typedef int *intptr;
int defstrchrnul = 1; 
//f (decl int defstrchrnul),
/*
    iff !ctxt->interactive
    thn defstrchrnul = 1;
    els blk
        stm printfflush("%sprooted? [y] ", GLOBAL_INDENT);
        chr *answer = mgetline("");
        stm
        iff !strncmp(answer, "y", 1)
        thn defstrchrnul = 0;
        iff !strncmp(answer, "n", 1)
        thn defstrchrnul = 1;
        stm defstrchrnul = 0;
        end
 */ 
//e

stm sh$$ "touch %s", ROOTC("/run/cwd.txt") $$;
stm sh$$ "touch %s", ROOTC("/run/status.txt") $$;

iff ctxt->interactive
thn printfflush("%s[press enter] ", GLOBAL_INDENT);

stm linebuf_t cflags;
stm cflags[0] = 0;

stm FILE *cmdlogfile = fopen(ROOTC("/run/log.txt"), "a");

#   define teeprintf(...)  \
	do { \
	    printf(__VA_ARGS__); \
	    fprintf(cmdlogfile, __VA_ARGS__); \
	while (0) \

rep
blk stm mdecl; 
    stm loadcwd(ctxt->rootworkdir); getcwd(ctxt->cwd, linebuf_tn);
    stm ctxt->linebuf[0] = 0;

    stm pchar cctxt = (pchar) ctxt;
    //f (decl pchar cmd, pass pchar cctxt),
        stm maincontext_t *ctxt = (maincontext_t *) cctxt;
        chr *cmd = mallocaddpagebuf;
        stm *cmd = 0;
        iff !ctxt->setemptyline && !ctxt->interactive
        thn stm *stpncpy(cmd, ctxt->argcmd, pagebuf_tn - 2) = 0;
        iff !ctxt->setemptyline &&  ctxt->interactive
        thn blk fgetallsclose(cmd, pagebuf_tn - 1, fopen(ROOTC("/insert.c"), "r"));
            stm fputsclose("", fopen(ROOTC("/insert.c"), "w"));
            iff strlen(cmd)
            thn printf("<insert.c>\n\n");
            els cmd = mgetline(mf("%s# %%02d $ ", GLOBAL_INDENT));
            blk_end
        iff ctxt->setemptyline
           thn blk
               stm cmd[0] = '\n';
               stm cmd[1] = 0;
               stm ctxt->setemptyline = 0;
        end_blk
    //e

    stm *stpncpy(ctxt->linebuf, cmd, pagebuf_tn - 2) = '\0';        
    stm ctxt->line = ctxt->linebuf;

    stm fputs(ctxt->line, cmdlogfile);
    
    stm linebuf_t runopt;
    stm runopt[0] = 0;
    // ctxt->line

    #define ctxtmatchcmd(pattern) \
        iff 0 == strncmp(ctxt->line, pattern, strlen(pattern)) \
         && (ctxt->line += strlen(pattern), 1) \
        thn

    stm ctxtmatchcmd("# exit")
    blk
        stm shdirect$$ "gcc %s %s -o%s", 
                CFLAGS(defstrchrnul), CINPUTFILES,
	        ROOTC("/a.out") $$ 
        stm ;exit(0);
    blk_end

    stm ctxtmatchcmd("# cmdlogexec")
    blk stm FILE *f = fopen(ROOTC("/run/log.txt"), "r"); 
        cen // if the last line of cmd log begins with [EXEC] $ ... cmd...
	stm // then remove that line and execute it
    blk_end

    stm ctxtmatchcmd("# restart") exit(5);
    
    stm ctxtmatchcmd("# runopt ") 
    blk 
           ctxt->line[strlen(ctxt->line) - 1] = 0;
               
        strncpy(runopt, ctxt->line, linebuf_tn - 1);
        runopt[linebuf_tn - 1] = 0;
   
           ctxt->line = ctxt->line + strlen(ctxt->line);
    end

    stm ctxtmatchcmd("# cflags ") 
    blk 
           ctxt->line[strlen(ctxt->line) - 1] = 0;
               
        strncpy(cflags, ctxt->line, linebuf_tn - 1);
        runopt[linebuf_tn - 1] = 0;
   
           ctxt->line = ctxt->line + strlen(ctxt->line);
    blk_end

    stm ppchar pline = &ctxt->line;
    stm pchar linebuf = ctxt->linebuf;
    stm pchar cwd = ctxt->cwd;
    stm pchar rootworkdir = ctxt->rootworkdir;
    //f fnc (pass ppchar pline, pass pchar linebuf, pass pchar cwd, pass pchar rootworkdir),
    
    stm ctxtmatchcmd("# cd ")
        blk
        stm (*pline)[strlen(*pline) - 1] = 0;
        
        int isroot = strlen(*pline) && (*pline)[0] == '/';
        
        stm fputsclose(
                mf("%s/%s/\n", isroot ? "" : cwd, (*pline)), 
                fopen(ROOTC("/run/cwd.txt"), "w")
            );
        stm loadcwd(rootworkdir);
	stm fflush(cmdlogfile);
	stm fputsclose(GLOBAL_INDENT, fopen(ROOTC("/run/log.txt"), "a"));
	stm sh, "pwd >> %s", ROOTC("/run/log.txt"), endsh;        
            // ctxt->line = ctxt->line + strlen(ctxt->line);
        stm *pline = linebuf;
        stm (*pline)[0] = 0;               
        blk_end    
    //e end

    ign mainremoveunescnl(ctxt->line);
    stm mainprintsubmainbegin(ctxt);
    stm mainprintsubmainend(ctxt);    

    stm sh, "%s %s %s %s", "mv -f", ROOTC("/run/a.out"), ROOTC("/run/b.out"), QUIET, endsh;

//EVALECHO(
    chr flags[256];
    stm snprintf(flags, 254, " %s %s", CFLAGS(defstrchrnul), cflags);
    chr ccmd[1024];
    stm snprintf(ccmd, 1020, "%s %s %s -o%s", "gcc", flags, CINPUTFILESRUN, ROOTC("/run/a.out"));
    //stm es$ ccmd $ 
   ;int compilestatus;
        // :syntax keyword Statement stm
    stm if (!fork()) { execl("/bin/sh", "sh", "-c", ccmd, (char *) NULL); };
    int lines = 0;
    int ms, lastms = 0;
    #   define animf(...) \
        do { \
            if (ctxt->interactive) \
                printfflush(__VA_ARGS__); \
        } while (0)
    #   undef animf
    #   define animf(...)
    stm animf("\n\n\n\n\n\n\n\n\n");
    rep blk
        
        stm struct timespec  ts;
        iff clock_gettime(CLOCK_REALTIME, &ts) == -1
        the ms = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
        iff (ms - lastms > 90)
        thn blk
            chr *line =
"# # # #        # # # #        # # # #        ";
            //chr *line = "          # # # # # # # # #           # # # # # # # # #           # # # # # # # # # ";
            chr modline[strlen(line) + 1];
            stm modline[strlen(line)] = 0;
            stm animf("\033[2K\033[T\033[2K\033[T\033[2K\033[T\033[2K\033[T\033[2K\033[T\033[2K\033[T\033[2K\033[T\033[2K\033[T");
            for (int j = 0; j < 8; ++j)
            blk for (int i = 0; i < strlen(line); ++i)
                stm modline[i] = line[(i + lines * 4 + j * 0) % strlen(line)];
                stm animf("%s\n", (j % 2) ? "" : modline);
            end 
            stm ++lines;
            stm lastms = ms;
            end 
        
        int wstatus;
        //s wait   (&wstatus);
        iff ({int r = waitpid(-1, &wstatus, WNOHANG);
              if (r == -1) goto err;
              r;}) 
         && WIFEXITED(wstatus)
        thn {compilestatus = WEXITSTATUS(wstatus); break;}
        end 

    stm animf("\033[2K\033[T\033[2K\033[T\033[2K\033[T\033[2K\033[T\033[2K\033[T\033[2K\033[T\033[2K\033[T\033[2K\033[T");
        
//   )

    iff !SYSTOBOOL(compilestatus)
    thn blk
        iff !strncmp(ctxt->linebuf, " ", 2)
        thn ctxt->setemptyline = 1;
        els ign blk
                ifn sh, "%s %s %s", "stat", mf("%s%s", ctxt->rootworkdir, ".err"), QUIET, endsh
                thn printf("%s\n", mf("%s%s %s", ctxt->rootworkdir, ".err", "already exists"));
                els blk
                    stm iff mv, ctxt->rootworkdir, mf("%s%s", ctxt->rootworkdir, ".err"), endsh
                    the iff cpr, mf("%s%s", ctxt->rootworkdir, ".bak"), ctxt->rootworkdir, endsh
                    the 
                    end 
                end 
        end 
    
    iff SYSTOBOOL(compilestatus) 
    thn 
    blk

    stm //ed$ malloclist->nptrs $
   
   ;stm cp, ctxtmwf("a.out"), "/data/data/com.termux/files/home/a.out", endsh;
    stm chmodx, "/data/data/com.termux/files/home/a.out", endsh;

    stm fclose(cmdlogfile);
   
    stm cmdlogfile = fopen(ROOTC("/run/tmp/log.next.txt"), "a");

    int stdoutfileno = dup(STDOUT_FILENO);
    stm FILE *faout =
            popen (mf("%s %s %d", runopt, "stdbuf -o0 /data/data/com.termux/files/home/a.out", stdoutfileno), "r"); 
    //s sh, "/data/data/com.termux/files/home/a.out", endsh;

    int in = ctxt->interactive;

#undef ᛪ
#define ᛪ(...)

    int faoutflags = fcntl(fileno(faout), F_GETFL, 0);
    fcntl(fileno(faout), F_SETFL, faoutflags | O_NONBLOCK);

    struct pollfd pfd;
    pfd.fd = fileno(faout);
    pfd.events = POLLIN;

    int runstatus = 0xFF;
    int dolineprefix = 1; 
    rep blk ᛪ(faout, cmdlogfile, stdout, /*pid*/-1, runstatus)
            # define dlp dolineprefix 
        rep blk
            chr line [linebuf_tn];
	        iff ({fflush(faout); poll(&pfd, 1, 100) <= 0 || !fgetsnonl(line, linebuf_tn, faout);})
	        thn break;
	        stm if ( in) printfflush ("%s%s%s", dlp ? GLOBAL_INDENT : "", dlp ? "> " : "", line);
	        stm if ( in) fprintf (cmdlogfile, "%s%s%s", dlp ? GLOBAL_INDENT : "", dlp ? "> " : "", line);
            stm if (!in) printfflush ("%s", line); 
            stm dolineprefix = line[strlen(line)-1] == '\n';
            end 
        int wstatus;
        iff ({int r = waitpid(-1, &wstatus, WNOHANG);
              if (r == -1 && errno != ECHILD) goto err;
              r;}) 
         && WIFEXITED(wstatus)
        thn {runstatus = WEXITSTATUS(wstatus); break;}
        stm sleep(1);
        end

    stm if (faout) pclose(faout);

    stm fclose (cmdlogfile);
    stm cat$$ mf("%s >> %s", ROOTC("/run/tmp/log.next.txt"), ROOTC("/run/log.txt")) $$
   ;stm mv$$ ROOTC("/run/tmp/log.next.txt"), ROOTC("/run/tmp/log.next.txt.bak") $$
   ;iff ctxt->interactive
    thn blk printfflush("%sPress 'k' to keep command output...", GLOBAL_INDENT);
        int answer = unbufreadc(STDIN_FILENO); 
        iff answer != 'k' 
        thn mv, ROOTC("/run/tmp/log.last.txt"), ROOTC("/run/log.txt"), endsh; 
        stm {sh, "clear", endsh; sh, "tail --lines=240 %s", ROOTC("/run/log.txt"), endsh;}
        end 
    stm cmdlogfile = fopen(ROOTC("/run/log.txt"), "a");

    stm cp, ROOTC("/run/log.txt"), ROOTC("/run/tmp/log.last.txt"), endsh;

    iff ctxt->interactive
    thn statusprint(ROOTC("/run"), runstatus, getstdout(), cmdlogfile);

    iff !nextbackup--
    thn blk
        stm nextbackup = 10,
        stm rmr, mf("%s%s", ctxt->rootworkdir, ".bak"), 
               /*mf("%s%s", ctxt->rootworkdir, ".bak.bak"),*/ endsh;
        stm mv,  mf("%s%s", ctxt->rootworkdir, ".tmp.bak"),
                 mf("%s%s", ctxt->rootworkdir, ".bak"), endsh;
        stm cpr, mf("%s%s", ctxt->rootworkdir, ""),
                 mf("%s%s", ctxt->rootworkdir, ".tmp.bak"), endsh;
    end end 

    iff !ctxt->interactive
    thn break;

   ;stm strcpy(ctxt->lastline, ctxt->linebuf);
    stm ctxt->isfirstcmd = 0;
    stm mfree;
blk_end

    return 0; 

err:
iff errno
thn perror(mf("%s:%d", __FILE__, __LINE__));
els printf("Error at %s:%d\n", __FILE__, __LINE__);
    return 1;
end

malloclist_t *malloclist;

int main(int iargc, char **iargv) 
blk
//s uiunbuffered();

stm minit;
chr *cmd = NULL;

iff 2 < iargc
 && !strncmp(iargv[1], "-c", 3)
thn blk
    iff 3 < iargc
    the cmd = iargv[2];     
    end

int argc = 3;
chr *argv[3] = {"bytesh", ROOTC("/run/"), cmd};

stm maincontext_t *ctxt = mallocadd(sizeof(maincontext_t));
stm ctxt->isfirstcmd   = 1;
stm ctxt->syssh        = 0;
stm ctxt->lastline     = mallocadd(10 * linebuf_tn);
stm ctxt->lastlinen    = 110 * linebuf_tn;
stm ctxt->cwd          = mallocaddlinebuf;
stm ctxt->setemptyline = 0;
stm ctxt->linebuf      = mallocaddpagebuf;
stm ctxt->rootworkdir  = trimmatchingend(ctxt->rootworkdir = rootworkdir = ROOTC("/run/"), '/');
stm ctxt->interactive  = !cmd;
stm ctxt->argcmd       = cmd;


stm innermain(ctxt);
stm return 0;

err:
stm printf("Usage: %s [-c <command>]\n", 0 < iargc ? iargv[0] : "bytesh");
stm return 1;
end

chr *whitestatus() 
blk
chr *status mpushlinebuf;
stm FILE *statusfile = fopen(ROOTC("/run/status.txt"), "r");
rep ifn fgets(status, linebuf_tn, statusfile)
    thn break;
stm fclose(statusfile);
int skipstatuslen = strlen(status) - 5;
iff skipstatuslen < 0
thn skipstatuslen = 0;
chr *skipstatus = mallocadd(skipstatuslen + 1);
for range(0, skipstatuslen)
stm skipstatus[i] = ' ';
stm skipstatus[skipstatuslen] = 0;
stm return skipstatus;
end

chr *trimmatchingend(char *target, char ch)
blk
iff target[strlen(target) - 1] == ch
thn target[strlen(target) - 1] = 0;    
stm return target;
end

nil loadcwd(char *rootworkdir)
blk  
chr path[NBUF]; snprintf(path, NBUF, "%s/cwd.txt", rootworkdir);
stm // printf("path = '%s'\n", path);
chr line[NBUF]; fgetsclose(line, NBUF, fopen(path, "r"));
stm line[strlen(line) - 1] = 0;
stm // printf("line = '%s'\n", line);
int r = chdir(line);
iff r < 0 
thn blk
    stm printf("cd: error\n");
    stm fputsclose("/data/data/com.termux/files/home/prj/bytesh/", fopen(path, "w"));
    end

stm return 0;
end

nil mainprintsubmainbegin(maincontext_t *ctxt)
blk
    ctxt->srcfile = fopen(ctxtmwf("main.c"), "w");

chr *cwdinclude = mf( "%s/%s", ctxt->cwd, "/dir.h" );
iff SYSTOBOOL(access(cwdinclude, F_OK))
thn fprintf(ctxt->srcfile, "%s", mf("#include \"%s\"\n", cwdinclude));

    fprintf(ctxt->srcfile, "#include \"main.h\"\n");

stm cwdinclude = mf( "%s/%s", ctxt->cwd, "/dirpost.h" );
iff SYSTOBOOL(access(cwdinclude, F_OK))
thn fprintf(ctxt->srcfile, "%s", mf("#include \"%s\"\n", cwdinclude));
    fprintf(ctxt->srcfile, "\n");
    fprintf(ctxt->srcfile, "char *lastcmd = \"%s\";\n", 
        escapecstr(ctxt->lastline, ctxt->lastlinen));
    fprintf(ctxt->srcfile, "int main_interactive = %d;", ctxt->interactive);
    fprintf(ctxt->srcfile, "int syssh = %d;\n", ctxt->syssh);
    fprintf(ctxt->srcfile, "char *rootworkdir = \"%s\";", ctxt->rootworkdir);
    fprintf(ctxt->srcfile, "malloclist_t *malloclist;");
    fprintf(ctxt->srcfile, "int isfirstcmd = %d;", ctxt->isfirstcmd);
    fprintf(ctxt->srcfile, "\n");
    fprintf(ctxt->srcfile, "int main(int argc, char **argv) {\n");
    fprintf(ctxt->srcfile,     "minit;");
    fprintf(ctxt->srcfile,     "MAIN_BEGIN\n");    
    fprintf(ctxt->srcfile,     "#ifdef BYTESH_DISABLE_OPTIMIZATION\n");
    fprintf(ctxt->srcfile,     "EVALECHO (\n");
    fprintf(ctxt->srcfile,     "#endif\n");

stm return 0;
end

nil mainremoveunescnl(char *line)
blk for (unsigned long i = 1; i < strlen(line); ++i)
    iff line[i] == '\n' 
     || line[i] == (char)10
    thn iff line[i-1] != '\\'
        thn line[i] = ' ';
stm return 0;
end

nil mainprintsubmainend(maincontext_t *ctxt)
blk fprintf(ctxt->srcfile,     "%s\n", ctxt->line);
stm fprintf(ctxt->srcfile,     "#ifdef BYTESH_DISABLE_OPTIMIZATION\n");
stm fprintf(ctxt->srcfile,     ")\n");
stm fprintf(ctxt->srcfile,     "#endif\n");        
stm fprintf(ctxt->srcfile,     "\nMAIN_END");
stm fprintf(ctxt->srcfile, "}");    
stm fclose(ctxt->srcfile);
stm return 0;
end


//)
