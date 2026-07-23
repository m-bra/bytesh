#define CFLAGS(defstrchrnul) defstrchrnul == -1 ? CFLAGS_(1) : CFLAGS_(defstrchrnul) 

#define CFLAGS_(defstrchrnul) mf( "-g -lcurl -ljansson -Wno-unused-command-line-argument -Wfatal-errors " "-DBYTESH_DISABLE_OPTIMIZATION " "-I%s/../arrfile/ " "%s", ROOT, defstrchrnul ? "-DDEFSTRCHRNUL" : "" )

#define CINPUTFILES    mf(     "%s/main.c %s/run/*.o %s/../arrfile/arrfile.c", ROOT, ROOT, ROOT)

#define CINPUTFILESRUN mf( "%s/run/main.c %s/run/*.o %s/../arrfile/arrfile.c", ROOT, ROOT, ROOT)


#if 0

prj="/storage/self/primary/prj/" ;

function cflags()
{
     test "$1" == "" && echo $(cflags_ 1)
     test "$1" == "" || echo $(cflags_ "$1")
}

function cflags_()
{
    defstrchrnul=
    test "$1" == "1" && defstrchrnul="-DDEFSTRCHRNUL"
    test "$1" == "1" || defstrchrnul=""
    echo "-g -lcurl -ljansson -Wno-unused-command-line-argument -Wfatal-errors -DBYTESH_DISABLE_OPTIMIZATION -I $prj/arrfile/ $defstrchrnul" ; 
}

function cinputfiles()
{
    echo "$prj/bytesh/main.c $prj/bytesh/run/*.o $prj/arrfile/arrfile.c";
}


function cinputfilesrun()
{
    echo "$prj/bytesh/run/main.c $prj/bytesh/run/*.o $prj/arrfile/arrfile.c";
}

alias make="gcc $(cinputfiles) $(cflags)"

#endif
