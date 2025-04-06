#define testdef123 123
#define mvlsy mv "localsys-main"
#define clear sys "clear" _
#define tputsc sys "tput sc" _
#define tputrc sys "tput rc" _
#define repeat(n) for (int i = 0; i < n; ++i)


#define longtext repeat(100) {pfs "hello, world" _ ln}

#define mpv(s) sys \
    (\
        snprintf(\
            mallocadd(sizeof(linebuf_t)), \
            sizeof(linebuf_t), \
            "mpv %s", s\
        ),\
        lastmalloc\
    ) _

#define quickdefh edit ROOTC("/run/quickdef.h") _

#define storagepath "/storage/emulated/0/"

#define s "%s"



#define lnsfn(a, b) sys (mallocadd(sizeof(linebuf_t)), snprintf(lastmalloc, sizeof(linebuf_t), "ln -s %s %s", a, b), lastmalloc) _

#define lns lnsfn (


