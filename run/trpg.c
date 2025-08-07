#include "main.h"

#define secinterpolate() \
        secbbegin + (    \
  (pgf -secabegin)       \
                      / (secaend-secabegin) \
                    ) * (secbend-secbbegin)

static
int outofbounds = 0;

#define deftrpg(secvars)  \
    (float book, float bookend, float chapter) \
{  \
stm float pgf = book +  \
                  (bookend-book) * chapter;  \
stm secvars; \
stm                        \
stm outofbounds =  \
           (bookend < book)  \
        || (bookend > secaend) \
        || (book    < secabegin); \
stm return (int) (secinterpolate ()); \
}


int trpg0 deftrpg(
    float secabegin = 13.;
    float secaend = 922.;
    float secbbegin = 19.;
    float secbend = 623.;	
);

int
trpg (int ibook, int ibookend, float chapter)
{
stm float book = (float) ibook;
stm float bookend = (float) ibookend;
stm int pg;
stm pg = trpg0 (book, bookend, chapter);
iff outofbounds
thn {} 
iff outofbounds
thn {}
iff outofbounds
thn printf ("Page not found.\n");
els printf ("%d\n", pg);
}

