#define getdateh printf("%s", "Found in: $ tmph\n")
#define getdate 
#define sh$ sh ,
#define dsh$ directsh$
#define directsh$ shdirectout(mf(
#define $$ , "" )

#define TROOTC(path) mf("%s%s", "/data/data/com.termux/files/", path)

#include <fcntl.h>
#include <sys/stat.h>

#define code776 "hello"

#define cplt cmdlogpop$$ "latest" $$
#define cllt cplt

#define cptr cmdlogpop$$ "trash" $$
#define cltr cptr

#define cpbt cmdlogpop$$ "bytesh.tweaks" $$
#define clbt cpbt

#define clmn cmdlogpop$$ "mntc" $$
#define cpmn clmn

#define clex cmdlogpop$$ "examples" $$
#define cpex clex

#define stardict shdirect$$ "less %s", ROOTC("/run/tmp/stardict.txt") $$

//char *mmap2(char const *filename, 

/*void mmaptest() 
{
    struct stat statbuf;
    int fd = open("/some/shared/resource/file", "r");
    fstat(fd, &statbuf);

    // Creating a read only, shared, file backed memory allocation
    int *shared = mmap(
         addr=  NULL,
         length=  statbuf.st_size - 1,
         prot=  PROT_READ, // | PROT_WRITE 
         flags=  MAP_SHARED,
         fd=  fd,
         offset=  0);
}*/ 
#define cdhome cd$$ "/T/home/mbrandt" $$

#define cdbytesh cd$$ ROOTC(".") $$

#define cdup cd$$ ".." $$

# define gitstatus sh$$ "git status" $$

# define less$$ shdirect$$ "less %s",

# define ccolors edit$$ "~/.vim/after/syntax/c.vim" $$

# define addckeyword$$ sh$$ "echo 'syntax keyword Keyword %s' >> ~/.vim/after/syntax/c.vim",

# define ssp(p) mf$ "/storage/self/primary/%s", p $

#define buildc edit$$ "run/build.c" $$

# define arrfileh edit$$ ROOTC("/../arrfile/arrfile.h") $$

# define test readarrfile("N26LATEST.UPPER")

#define buerokrfin(p) mf$ "/storage/emulated/0/MEGABUEROKRATIE/FINANZEN/%s", p $



# define arrfilec edit$$ ROOTC("../arrfile/arrfile.c") $$



# define m5$$ shdirect$$ "PATH=\"$PATH:%s/m5/bin/\" cat %s | m5", ROOTC("/../"),



# define m5root ROOTC("../m5/")

# define pkgi$$ sh$$ "pkg install %s",
# define pkgs$$ sh$$ "pkg search %s",
#

# define termuxhome(p) mf( "/data/data/com.termux/files/home/%s", p )

# define touch$$ sh$$ "touch %s",
# define cargobuildrel sh$$ "CARGO_MSG_LIMIT=1 cargo lbuild --release > cargo.out 2>&1 ; cat cargo.out ; cat cargo.out | chooseedit" $$

# define echo$$ sh$$ "echo %s",

# define vim$$ edit$$

# define prjm5(p) termuxhome(mf( "prj/m5/%s", p ))

# define prjbytesh(p) termuxhome(mf( "prj/bytesh/%s", p ))

/*# define llamareqc$$ sh$$ \
    "curl -sS "\
	"http://localhost:8080/v1/messages"\
	"--header 'Content-Type: application/json'"\
	"--data '{"\
	    "\"system\": \"You are a coding assistant. Print nothing before or after your generated C code.\","\
	    "\"max_tokens\": 128,"\
	    "\"messages\": [{\"role\": \"user\", \"content\": \"%s\"}]"\
	"}' | jq -r '.content[0].text' | sed 's/\\\\n/\\n/g'", 
*/
/*curl http://localhost:8080/v1/messages   -H "Content-Type: application/json"   -d '{
    "max_tokens": 256,
    "system": "You are a helpful assistant.",
    "messages": [
      {"role": "user", "content": "Write the longest piece of arbitrary C code you can using the stdio library. Write nothingn else than just the code. No other phrases."}
    ]                                                                                                                    }' | jq -r '.content[0].text'*/

void llamacomplete(char *msg);

# define llamacomplete$$ sh$$ \
    "curl -sS --request POST "\
        "--url http://localhost:8080/completion "\
        "--header \"Content-Type: application/json\" "\
        "--data '{\"prompt\": \"%s\", \"n_predict\": %d}' | jq -r '.content'",

# define llamamsg$$ sh$$ \
  "curl -sS http://localhost:8080/v1/messages   -H \"Content-Type: application/json\"   -d '{"\
  "\"max_tokens\": 64,"\
  "\"system\": \"\","\
  "\"messages\": ["\
  "   {\"role\": \"user\", \"content\": \"%s\"}"\
  " ] "\
  "}' | jq -r '.content[0].text'",

# define llamamsgc$$ sh$$ \
  "curl -sS http://localhost:8080/v1/messages   -H \"Content-Type: application/json\"   -d '{"\
  "\"max_tokens\": 64,"\
  "\"system\": \"You are a coding assistant. Generate C code only.\","\
  "\"messages\": ["\
  "   {\"role\": \"user\", \"content\": \"%s (In your response, do not give any explanation or commentary whatsoever.)\"}"\
  " ] "\
  "}' | jq -r '.content[0].text'",

#define _IOFBF 0  /* Full buffering */
#define _IOLBF 1  /* Line buffering */
#define _IONBF 2  /* No buffering */

// test

# define test444 \
    int setvbuf(FILE *stream, char *buf, int mode, size_t size);\
    setvbuf(getstdout(), 0, _IONBF, 0);\
    for seqto(i, 5) {\
        printf("hello, ");\
        fsync(fileno(getstdout()));\
        sleep(1);\
    }
# define tmpc vim$$ ROOTC("/run/tmp.c") $$

# define test564 llamacomplete("int a = 0; int b = a + /*fibonacci*/ ")

# define stdioextc vim$$ ROOTC("/run/stdioext.c") $$

# define llamacomplete2(x) using_original_stdout(llamacomplete(x))

