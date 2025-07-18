#include "main.h"

#ifndef INCLUDEDMNTCH
#define INCLUDEDMNTCH

#define mntch edit, ROOTC("/run/mntc.h"), endsh
#define mntchadd hadd("mntc")
#define mntchaddfn(ident) haddfn("mntc", ident)
#define mntchadddef(ident) hadditem("mntc", ident, 1)

extern int lastresult;

int routine_gitupdaterequired(int, char *);

#endif
