#undef find$$
#define findgrep$$ sh$$ "find main.c run -not -type d | xargs grep %s ", 

/*
    > -rw-rw----  1 10182 1023  85K Sep 25 16:50 a.out
    > drwxrws---  2 10182 1023 3.4K Sep 14 12:49 .bak
    > -rw-rw----  1 10182 1023  148 Sep 11 13:33 cflags.h
    > -rw-rw----  1 10182 1023   49 Sep 25 18:57 dirpost.h
    > drwxrws---  7 10182 1023 3.4K Sep 25 18:56 .git
    > -rw-rw----  1 10182 1023  113 Aug 16 15:41 .gitignore
    > -rw-rw----  1 10182 1023    0 Sep 25 18:57 insert.c
    > drwxrws---  4 10182 1023 3.4K Feb 13  2025 localsys-main
    > -rw-rw----  1 10182 1023  15K Sep 14 13:13 main.c
    > -rw-rw----  1 10182 1023  14K Aug  9 20:13 main.c.orig
    > -rw-rw----  1 10182 1023  946 Aug  9 20:06 main.c.rej
    > -rw-rw----  1 10182 1023  14K Aug 10 14:11 main.hiddencmd.c
    > -rw-rw----  1 10182 1023  232 Sep 11 12:56 repopw.txt
    > drwxrws--- 12 10182 1023 4.0K Sep 25 18:57 run
    > drwxrws--- 12 10182 1023 4.0K Sep 24 11:00 run.bak
    > drwxrws--- 12 10182 1023 4.0K Sep 24 18:08 run.tmp.bak
*/

