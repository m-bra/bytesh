#ifndef STDLIBEXTH_INCLUDED
#define STDLIBEXTH_INCLUDED

#include "main.h"

#define MALLOCLISTDEBUG if (0)

#define INSERT_OPENING_PAREN (
#define INSERT_CLOSING_PAREN )
#define $ INSERT_CLOSING_PAREN 

#ifndef NOEVAL
#define ed(x) printf("(int) (%s) = %d \n", #x, (int) (x));
#define ed$ ed___ INSERT_OPENING_PAREN
#define ed__(x) ed(x)
#define ed___ ed__
#define ec(x) printf("(char) (%s) = '%c' \n", #x, (char) (x) == '\n' ? "\\n" : (char) (x));
#define ef(x) printf("(float) (%s) = %f \n", #x, (float) (x));
#define ef__(x) ef(x)
#define ef___ ef__
#define ef$4 ef___ INSERT_OPENING_PAREN INSERT_OPENING_PAREN INSERT_OPENING_PAREN INSERT_OPENING_PAREN

char *es_(char *name, char *sz);
#define es__(x) es_(#x, x)
#define es___ es__
#define es$ es___ INSERT_OPENING_PAREN
#endif

#define MALLOCLISTMAXPTRS 2048000
typedef struct
{
	void *ptrs[MALLOCLISTMAXPTRS];
	int nptrs;
} malloclist_t;
#define lastmalloc (malloclist->ptrs[malloclist->nptrs - 1])

#define mdecl \
  malloclist_t malloclistobj;\
  malloclist_t *malloclist = &malloclistobj;

void *mallocadd_(malloclist_t *pmalloclist, int size);
#define mallocadd(size) mallocadd_(malloclist, size)

void mfree_(malloclist_t *malloclist);
#define mfree mfree_(malloclist)

extern malloclist_t malloclistval;
extern malloclist_t *malloclist;


#define breakpt ; {printf("breakpt at %s:%d", __FILE__, __LINE__);char c[8]; fgets(c, 8, getstdin());};

#define in(a, f, b) f ( a , b )

#define ANONSTRUCT_COUNT_(x) anon_struct##x
#define ANONSTRUCT_COUNT(x) ANONSTRUCT_COUNT_(x) 

#define SECTION
#define TEXT struct ANONSTRUCT_COUNT(__COUNTER__) {
#define FUNCTION blk_end ;
#define def blk 
#define DATA blk_end ;

#define dat DATA
#define txt TEXT

#define looph printf("#define loop (1)\n");
#define loop (1)
#define range(from, to) (int i = from; i < to; ++i)
#define reph printf("REPeat infinitely\n#define rep while (1)\n");
#define rep while (1)
#define ign if (0)
#define iffh printf("IF and only iF \n#define iff if ( (\n");
#define iff if (   (
#define ifnh printf("IF Not \n#define ifn if ( ! (\n");
#define ifn if ( ! (
#define thnh printf("THeN\n#define thn ) )\n");
#define thn ) )
#define chr char
#define elsh printf("ELSe\n#define els else\n");
#define els else
#define cenh printf("Catch ErrNo (after instr) (singular instr)\n#define cen if (errno != 0) goto err;\n");
extern int cen_line;
#define cen if (geterrno() != 0) {cen_line = __LINE__; goto err;}
#define cefh printf("Catch EoF (before instr) (paired with thn/the)\n#define cef if (EOF ==\n");
#define cef if (EOF == (
#define theh printf("THen Err\n#define the thn goto err;\n");
#define the thn goto err;
#define stmh printf("STateMent\n#define stm\n");
#define stm
#define s
#define nop

#ifdef BETTER_BLK
    #define blkh printf("BLocK\n#define blk {");
    #define blk blk1 blk2
    #define blk1 blk3
    #define blk2 (
    #define blk3(...) {__VA_ARGS__}
    #define blk_endh printf("BLocK END\n#define blk_end }");
    #define blk_end end_
    #define end_blkh printf("END BLocK\n#define end_blk }")
    #define end_blk end_
#else
    #define blkh printf("BLocK\n#define blk {");
    #define blk {
    #define blk_endh printf("BLocK END\n#define blk_end }");
    #define blk_end }
    #define end blk_end
    #define end_blkh printf("END BLocK\n#define end_blk }")
    #define end_blk }
#endif

#define then ) )
#define ift if (   (

#define asstr (char *)
#define asmem (char *)
#define nil int

#define throwngerrno(x)                      \
    if (x < 0) {                             \
        printf("Error at ");                 \
  	    printf("%s:", __FILE__);             \
  		printf("%d\n", __LINE__);            \
  		printf("%s\n", strerror(geterrno()));\
  		exit(1);                             \
  	}                                        \
//

#include <stdarg.h>

char *mlinebufprintf_(malloclist_t *malloclist, char *fmt, ...);
#define mlinebufprintf(...) mlinebufprintf_(malloclist, __VA_ARGS__)
#define malloclinebufprintf mlinebufprintf
#define mf mlinebufprintf
#define mf$ mlinebufprintf INSERT_OPENING_PAREN

char *es_(char *name, char *sz);

#define BOOLTOSYS(b) (!(b))
#define SYSTOBOOL(b) (!(b))

#define spawn(code)     \
    do {                \
    	if (!fork()) {  \
    		code        \
    	}               \
    } while (0)         //

int sh_(int ignored, char *fmt, ...) ;
int shdirectout(char *, char *fmt, ...);
int shfd_(int ignored, char *fmt, ...);
FILE *psh_(int ignored, char *fmt, ...);

#define shdirect$$ shdirectout ( 0,
#define sh$$ sh_ ( 0 ,
#define sh sh_ ( 0
#define shfd$$ shfd_ ( 0 ,
#define shfd shfd_ ( 0
#define psh$$ psh_ ( 0 ,
#define psh psh_ ( 0
#define endsh "" )

#define seqto(i, n) (int i = 0; i < n; ++i)

nil *mmap2(char const *, int *);

#endif
 
