char * getTestA() {
    char *path = "/data/data/com.termux/files/home/prj/bytesh//run/prop/TestA";
    return loads(path);

}

void 
setTestA(char *val) {
    char *path = "/data/data/com.termux/files/home/prj/bytesh//run/prop/TestA";
    fputsclose(val, fopen(path, "w"));
}
