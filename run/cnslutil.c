#include "main.h"
#include <unistd.h>

void edit_(char const *path)
{
	rm, ROOTC("/run/cnslutil/diff.txt"), endsh;
	cp, path, ROOTC("/run/cnslutil/diff.txt"), endsh;
        int current_stdout_fileno = dup(STDOUT_FILENO);
	dup2(ORIGINAL_STDOUT_FILENO, STDOUT_FILENO);
	char buf[512];
	// simply switch from micro to vim
	snprintf(buf, 512, "vim %s", path);
	system(buf);
	dup2(current_stdout_fileno, STDOUT_FILENO);
        sh, "diff -C 5 %s %s", ROOTC("/run/cnslutil/diff.txt"), path, endsh; 
	// TODO: undefined escape rules in param strings
}

void micro_(int ignore, char const *path, char *ignore_)
{
    edit_(path);
}

void cmdlog_()
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

void cmdloghead(int iend)
{
	FILE *f = fopen(mf("%s/%s", rootworkdir, "/log.txt"), "r");
	linebuf_t buf;
	int linen = -1;
	while loop {
		linen+= 1;
		if (!fgets((char *) buf, linebuf_tn, f))
			break;
		if (linen < iend)
			printf("0x%05X .. $ %s", linen, (char *)buf);
	}

	fclose(f);
}

void cmdlogregion(int from, int to, char *buf)
{
	char *p = buf;
	for (int i = from; i < to; ++i) {
		cmdlogat(i, (linebuf_t *) p);
		p += strlen(p);
	}	
}

void cmdinsert(char *cmd)
{
	fputsclose(cmd, fopen(ROOTC("/insert.c"), "a"));
}

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

#undef syssleep
void syssleep(int ignore, char const *time, char *ignore_)
{
	linebuf_t buf;
	snprintf(buf, sizeof(buf), "sleep %s", time);
	system(buf);
	// TODO: undefined escape rules in param strings
}

#undef tputcup
void tputcup(int ignore, int col, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "tput cup %d 0", col);
	system(buf);
}

void mkdir_(int ignore, char *path, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "mkdir %s", path);
	system(buf);
	// TODO: undefined escape rules in param strings
}

void mkdirp_(int ignore, char *path, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "mkdir -p %s", path);
	system(buf);
	// TODO: undefined escape rules in param strings
}

int mv_(int ignore, char *from, char *to, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "mv %s %s", from, to);
	return system(buf);
	// TODO: undefined escape rules in param strings
}

void cp_(int ignore, char const *from, char const *to, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "cp %s %s", from, to);
	system(buf);
	// TODO: undefined escape rules in param strings
}

void rm_(int ignore, char *filename, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "rm %s", filename);
	system(buf);
	// TODO: undefined escape rules in param strings
}

void cat_(int ignore, char *filename, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "cat %s", filename);
	system(buf);
	// TODO: undefined escape rules in param strings
}

void touch_(int ignore, char *sz, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "touch %s", sz);
	system(buf);
	// TODO: undefined escape rules in param strings
}

void diff_(int ignore, char *from, char *to, char *ignore_)
{
	char buf[NBUF];
	snprintf(buf, NBUF, "diff %s %s", from, to);
	system(buf);
	// TODO: undefined escape rules in param strings
}

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

void hadditem(char *namepath, char *ident, int preprocessor)
{
	
int current_stdout_fileno = dup(STDOUT_FILENO);
stm dup2(ORIGINAL_STDOUT_FILENO, STDOUT_FILENO);

chr *fnct = ident;
	
chr *name = strrstr(namepath, "/");
stm if ( name) name += 1;
stm if (!name) name = namepath;
	
chr *cmd = mf("%sh", name);
chr *filepath = mf("%s.h", namepath);
	
chr *prompt = mf("    [....] %sadd%s $ ", cmd, fnct ? (preprocessor ? "def" : "fn") : "");
stm printf("%s", prompt); fflush(getstdout());
		
chr space[] = "                                 ";
stm space[strlen(prompt) - 5] = 0;
chr *szdef = mgetline(mf("%s%%02d $ ", space));
   
chr *path = ROOTC(mf("/run/%s", filepath));

chr szdefb[strlen(szdef) + 2];
stm strcpy(szdefb, szdef);
stm szdefb[strlen(szdef)] = '\n';
stm szdefb[strlen(szdef) + 1] = 0;

stm FILE *f = fopen(path, "a");
stm fnct&&fputs(mf("#define %sh printf(%c%%s%c, %cFound in: $ %s%cn%c)%c", 
	             fnct, '"', '"', '"', cmd, BACKSLASH, '"', *NLS), f);

	int pp =  preprocessor;
	int np = !preprocessor;
	np&&fnct&&fputs(mf("void %s()%c", ident, *NLS), f);
	np&&fnct&&fputs(   mf("{%c", *NLS),      f);
	np&&      fputs(       szdefb, f);
	np&&fnct&&fputs(   mf("}%c", *NLS),      f);
	pp&&fnct&&fputs(mf("#define %s %s%c", ident, szdefb, *NLS), f);

stm dup2(current_stdout_fileno, STDOUT_FILENO);
stm printf("%s%s", prompt, szdefb);
}

#undef programm
void programm()
{
	linebuf_t path = "";
	snprintf(path, sizeof(linebuf_t), "%s%s", ROOT, "/run/programm.txt");
	edit, path, endsh;
}

#undef echosys
void echosys(char const *cmd)
{
    printf("\n[auto]\n");
	printf("$ %s\n\n", cmd);
	system(cmd);
}

#undef gitupdate
void gitupdate() {
    sh, "git add *", endsh;
    sh, "git add */*", endsh;
    sh, "git commit -m untitled", endsh;
    sh, "git push", endsh;
  //sh, "git status", endsh;
  //sh, "echo git status", endsh;
  //echosys "git log" _
}

#undef man
void man(int ignore, char *topic, char *ignore_) 
{
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

#undef du
void du(char * ignore, int depth, char *ignore2) {sh, "du -h -d %d", depth, endsh;}

#undef yays
int yays(int ignore, char *x, char *ignores)
{
	return sh, "yay -S %s", x, endsh;
}

#undef pacmans
int pacmans(int ignore, char *x, char *ignores)
{
	return sh, "sudo pacman -S %s", x, endsh;
}
int pacmanss_(int ignore, char *x, char *ignores)
{
int r = sh, "pacman -Ss %s > /tmp/pacmanss.txt", x, endsh;
iff SYSTOBOOL(r)
thn edit, "/tmp/pacmanss.txt", endsh;
stm return r;
}

#undef pacmanqi
int pacmanqi(int ignore, char *x, char *ignores)
{
	return sh, "pacman -Qi %s", x, endsh;
}

#undef pacmanql
int pacmanql(int ignore, char *x, char *ignores)
{
	return sh, "pacman -Ql %s", x, endsh;
}

#undef pacmanr
int pacmanr(int ignore, char *x, char *ignores)
{
	return sh, "sudo pacman -R %s", x, endsh;
}

int yayss_(int ignore, char *pkg, char *ignores)
{
	return sh, "yay -Ss %s", pkg, endsh;
}

#undef bak
void bak_(char *a, char *f, char *b)
{
	(void) a;
	(void) b;
	bakpre(f)
}

#undef pacmanyayss
int pacmanyayss(char *ignore, char *pkg, char *ignore2)
{
stm return (pacmanss, pkg, endsh) && (yayss,    pkg, endsh);
}

void cd$$_(char *ignore, char const *path, char *ignore2)
{
ign ignore;
ign ignore2;

    if (path[0] == '/')
    {
        sh, "printf '%s/' > %s", path, ROOTC("/run/cwd.txt"), endsh;
    }
    else 
    {
	sh, "printf '/%s/' >> %s", path, ROOTC("/run/cwd.txt"), endsh;
    }
}

int cmdlogpop(char *ignore, char *file, char *ignend)
{
         return
             shdirect$$ mf( \
                 "cd %s" " && " \
                 "vim  " \
     	         "-c 'normal G$v'" " -c '?^\\s\\s\\s\\s[^>]' " " -c 'normal d' " \
                      "-cw " " -c 'open log.%s.txt' " " -c 'normal G$p' " " -c wq "  \
     	         "%s" " && " \
                 "vim -c 'normal Gdddd' -cwq %s" " && " \
     	    "echo '' >> log.%s.txt", \
     	    ROOTC("/run/"), file, ROOTC("/run/log.txt"), ROOTC("/run/log.txt"), file ) $$; 
}
