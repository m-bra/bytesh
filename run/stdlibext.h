
#define breakpt ; {char c[8]; fgets(c, 8, stdin);};

#define in(a, f, b) f ( a , b )

#define loop (1)

#define throwngerrno(x)                     \
    if (x < 0) {                            \
        printf("Error at ");                \
  	    printf("%s:", __FILE__);            \
  		printf("%d\n", __LINE__);           \
  		printf("%s\n", strerror(errno));    \
  		exit(1);                            \
  	}                                       \
//
