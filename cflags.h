#define CFLAGS(defstrchrnul) \
    mf( "-Wfatal-errors " \ 
        "-DBYTESH_DISABLE_OPTIMIZATION " \ 
	"%s", defstrchrnul ? "-DDEFSTRCHRNUL" : "" )
