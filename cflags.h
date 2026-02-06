#define CFLAGS(defstrchrnul) defstrchrnul == -1 ? CFLAGS_(1) : CFLAGS_(defstrchrnul) 

#define CFLAGS_(defstrchrnul) \
    mf( "-g -Wfatal-errors " \
        "-DBYTESH_DISABLE_OPTIMIZATION " \
	"-I%s/../arrfile/ " \
	"%s", ROOT, defstrchrnul ? "-DDEFSTRCHRNUL" : "" )
#define CINPUTFILES    mf(     "%s/main.c %s/run/*.o %s/../arrfile/arrfile.c", ROOT, ROOT, ROOT)
#define CINPUTFILESRUN mf( "%s/run/main.c %s/run/*.o %s/../arrfile/arrfile.c", ROOT, ROOT, ROOT)
