#define curlh edit, ROOTC("/run/cnslutil/curl.h"), endsh
#define curlhadd hadd("cnslutil/curl")



# define curl sh, "curl --location %s"
# define curlgrep sh, mf("curl --location %%s %c grep %%s", PIPEC)
