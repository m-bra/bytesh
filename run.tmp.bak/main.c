#include "main.h"

char *lastcmd = "gpgdecrypt, \"repopw.txt\", endsh ";
int syssh = 0;
char *rootworkdir = "/data/data/com.termux/files/home/prj/bytesh//run";
int main(int argc, char **argv) {
MAIN_BEGIN
gpgdecrypt, "repopw.txt", endsh 
MAIN_END}