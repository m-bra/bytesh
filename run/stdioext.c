
#include <sys/wait.h>

struct SYSFILE;

struct SYSFILE *stdoutmacro();
struct SYSFILE *stdinmacro();
struct SYSFILE *stderrmacro();
int eofmacro();

struct SYSFILE *getstdout()
{
	return stdoutmacro();
}

struct SYSFILE *getstdin()
{
	return stdinmacro();
}

struct SYSFILE *getstderr()
{
	return stderrmacro();
}

int eof()
{
	return eofmacro();
}

#include <stdio.h>



#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NOSTRINGH
#define NOSTDIOH
#include "main.h"

struct SYSFILE *stdoutmacro()
{
	return (struct SYSFILE *) stdout;
}

struct SYSFILE *stdinmacro()
{
	return (struct SYSFILE *) stdin;
}

struct SYSFILE *stderrmacro()
{
	return (struct SYSFILE *) stderr;
}

int eofmacro()
{
	return EOF;
}

char *fgetsclose(char *sz, int n, FILE *f);

char *fgetm_(malloclist_t *malloclist, int n, FILE *f);

char *fgetmclose_(malloclist_t *malloclist, int n, FILE *f);

char *fgetallmclose_(malloclist_t *malloclist, int n, FILE *f);

int readm_(malloclist_t *malloclist, int fd, size_t size);

void fputsclose(char *sz, FILE *f);

char *loads(char *filename);


char *fgetsclose(char *sz, int n, FILE *f)
{
	int const NNULLCH = 1;
	char *result = sz;
	while ((n > NNULLCH) && fgets(sz, n, f))
	{
		n-= strlen(sz);
		sz+= strlen(sz);
	}
	fclose(f);
	return result;
}

char *fgetm_(malloclist_t *malloclist, int n, FILE *f)
{
	mallocadd(n);
	char *r = fgets(lastmalloc, n, f);
	return r ? lastmalloc : 0;	
}

char *fgetmclose_(malloclist_t *malloclist, int n, FILE *f)
{
	char *result = fgetm(n, f);
	fclose(f);
	return result;
}

char *fgetallmclose_(malloclist_t *malloclist, int n, FILE *f)
{
	mallocadd(n);
	return fgetallsclose(lastmalloc, n, f);
}

int readm_(malloclist_t *malloclist, int fd, size_t size)
{
	mallocadd(size);
	return read(fd, lastmalloc, size);
}

void fputsclose(char *sz, FILE *f)
{
	fputs(sz, f);
	fclose(f);
}

char *loads(char *filename)
{
	return fgetsclose(malloc(LOADBUFN), LOADBUFN, fopen(filename, "r"));
}

int waitpipe(pid_t senderpid, FILE *sender, FILE *receiver)
blk int runstatus = 0xFF;
    rep blk 
        rep blk
            chr line [linebuf_tn];
            stm fflush(sender); 
	    iff !fgets(line, linebuf_tn, sender)
	    thn break;
	    stm fprintf(receiver, "%s> %s", GLOBAL_INDENT, line);
	    end
        int wstatus;
        int r = waitpid(senderpid, &wstatus, WNOHANG);
        iff r == -1 && errno != ECHILD
    the iff r && WIFEXITED(wstatus)
        thn {runstatus = WEXITSTATUS(wstatus); break;}
        end 
    stm return runstatus;
err:
stm printf("Error from %s:%d\n", __FILE__, __LINE__);
stm return 111;
end

/**
 * fgetsnonl - Similar to fgets, but returns as soon as data is available.
 * @str: Buffer to store the output.
 * @size: Maximum number of characters to read (including null terminator).
 * @stream: The FILE stream to read from (e.g., faout).
 * * Returns: str on success, NULL on EOF or error.
 */
/*char *fgetsnonl(char *str, int size, FILE *stream) {
    if (size <= 1) return NULL;

    int fd = fileno(stream);
    
    // read() is a "blocking" call by default, but it returns 
    // as soon as ANY amount of data hits the pipe.
    ssize_t n = read(fd, str, size - 1);

    if (n <= 0) {
        return NULL; // EOF or Error
    }

    str[n] = '\0'; // Manually null-terminate
    return str;
}*/
char *fgetsnonl(char *str, int size, FILE *stream) {
    if (size <= 1) return NULL;

    int fd = fileno(stream);
    int i = 0;
    char c;

    // Read char-by-char until buffer is full or newline is hit
    while (i < size - 1) {
        ssize_t n = read(fd, &c, 1);

        if (n <= 0) {
            if (i == 0) return NULL; // EOF/Error on first char
            break;                   // EOF/Error after some data
        }

        str[i++] = c;

        if (c == '\n') break; // Found newline, stop reading
    }

    str[i] = '\0';
    return str;
}


