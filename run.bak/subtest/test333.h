#define test333h edit, ROOTC("/run/subtest/test333.h"), endsh
#define test333hadd hadd("subtest/test333")
#define test333haddfn(ident) haddfn("subtest/test333", ident)
#define test333hadddef(ident) hadditem("subtest/test333", ident, 1)


#define test3332h printf("%s", "Found in: $ test333h\n")
void test3332()
{
printf("success");

}
