#include "main.h"

#define preprocessorh edit, ROOTC("/run/preprocessor.h"), endsh

#define STRINGIFY(x) #x
#define EVALSTRINGIFY(x) STRINGIFY(x)
#define EVALSTRINGIFYPRINT(x) es(STRINGIFY(x))

#undef ECHO
#define ECHO(...) __VA_ARGS__ 
#define E(...) __VA_ARGS__
#define EVALECHO(...) ECHO(__VA_ARGS__)
#define APPLYMACRO_(x) x
#define APPLYMACRO(macroident, arglist) APPLYMACRO_(macroident arglist)

#ifdef BYTESH_DISABLE_OPTIMIZATION

#define WEREPASSED(...)
#define NOBRACKETS(...) __VA_ARGS__ 
#define UNPACK_ROUND_BRACKETS_B(f, x) f x 
#define UNPACK_ROUND_BRACKETS(x) \
	UNPACK_ROUND_BRACKETS_B(NOBRACKETS, x) UNPACK_ROUND_BRACKETS_B(WEREPASSED, x)

#define ECHO_NONEMPTY(x, ...) __VA_OPT__(x)
#define APPLYMACRO_NONEMPTYARGS(      macroident, arglist)         \
        APPLYMACRO_NONEMPTYARGSDIRECT(macroident, arglist)         //
#define APPLYMACRO_NONEMPTYARGSDIRECT(macroident, arglist)         \
    ECHO(                                                          \
        ECHO_NONEMPTY(macroident,  UNPACK_ROUND_BRACKETS(arglist)) \
        ECHO_NONEMPTY(arglist,     UNPACK_ROUND_BRACKETS(arglist)) \
    )                                                              //

#define ptr *
#define deltypeint
#define deltypevoid
#define deltypechar
#define deltypepchar
#define deltypeppchar
#define deltypepint
#define deltypenil

#define FNVPTRTYPEint   int *
#define FNVPTRTYPEpint  pint *
#define FNVPTRTYPEchar  char *
#define FNVPTRTYPEpchar pchar *
#define FNVPTRTYPEppchar ppchar *
#define FNVPTRTYPEfloat float *
#define FNVPTRTYPEpfloat pfloat *

#define object(...) object1(__VA_ARGS__)
#define object1(decl, ...) object1B(object1A_##decl,  __VA_ARGS__) 
#define object1A_     
#define object1A_int     decl , int
#define object1A_char    decl , char
#define object1A_float    decl , float
#define object1A_pint    decl , pint
#define object1A_pchar    decl , pchar
#define object1A_ppchar   decl , ppchar
#define object1A_pfloat    decl , pfloat
#define object1A_pvoid    decl , pvoid
#define object1A_pass pass ,
#define object1A_decl decl ,
#define object1B(tag, ...)  object1Bi(tag, __VA_ARGS__)
#define object1Bi(tag, ...) object1B_##tag(__VA_ARGS__)
#define object1B_(...)
#define object1B_pass(decl, ...) object1C(object1C_##decl, __VA_ARGS__)
#define object1B_decl(decl, ...) object1C(object1C_##decl, __VA_ARGS__)
#define object1C_int int ,
#define object1C_char char ,
#define object1C_float float ,
#define object1C_pint pint ,
#define object1C_pchar pchar ,
#define object1C_ppchar ppchar , 
#define object1C_pfloat pfloat ,
#define object1C_pvoid pvoid ,
#define object1C(decl, ...) object1Ci(decl,  __VA_ARGS__)
#define object1Ci(type, ident, ...) type ident; object2( __VA_ARGS__)
#define object2(decl, ...) object2B(object2A_##decl,  __VA_ARGS__) 
#define object2A_     
#define object2A_int     decl , int
#define object2A_char    decl , char
#define object2A_float    decl , float
#define object2A_pint    decl , pint
#define object2A_pchar    decl , pchar
#define object2A_ppchar   decl , ppchar
#define object2A_pfloat    decl , pfloat
#define object2A_pvoid    decl , pvoid
#define object2A_pass pass ,
#define object2A_decl decl ,
#define object2B(tag, ...)  object2Bi(tag, __VA_ARGS__)
#define object2Bi(tag, ...) object2B_##tag(__VA_ARGS__)
#define object2B_(...)
#define object2B_pass(decl, ...) object2C(object2C_##decl, __VA_ARGS__)
#define object2B_decl(decl, ...) object2C(object2C_##decl, __VA_ARGS__)
#define object2C_int int ,
#define object2C_char char ,
#define object2C_float float ,
#define object2C_pint pint ,
#define object2C_pchar pchar ,
#define object2C_ppchar ppchar ,
#define object2C_pfloat pfloat ,
#define object2C_pvoid pvoid ,
#define object2C(decl, ...) object2Ci(decl,  __VA_ARGS__)
#define object2Ci(type, ident, ...) type ident; object3(pass, __VA_ARGS__)
#define object3(...)

/*
#define STRUCTBODY(pr, ...) STRUCTBODY1(pr, __VA_ARGS__)
#define STRUCTBODY1(pr, decl, ...) STRUCTBODY1B(pr, STRUCTBODY1A_##decl,  __VA_ARGS__) 
#define STRUCTBODY1A_     
#define STRUCTBODY1A_int     decl , int
#define STRUCTBODY1A_char    decl , char
#define STRUCTBODY1A_float    decl , float
#define STRUCTBODY1A_pint    decl , pint
#define STRUCTBODY1A_pchar    decl , pchar
#define STRUCTBODY1A_pfloat    decl , pfloat
#define STRUCTBODY1A_pvoid    decl , pvoid
#define STRUCTBODY1A_pass pass ,
#define STRUCTBODY1A_decl decl ,
#define STRUCTBODY1B(pr, tag, ...)  STRUCTBODY1Bi(pr, tag, __VA_ARGS__)
#define STRUCTBODY1Bi(pr, tag, ...) STRUCTBODY1B_##tag(pr, __VA_ARGS__)
#define STRUCTBODY1B_(...)
#define STRUCTBODY1B_pass(pr, decl, ...) STRUCTBODY1C(pr, STRUCTBODY1C_##decl, __VA_ARGS__)
#define STRUCTBODY1B_decl(pr, decl, ...) STRUCTBODY1C(pr, STRUCTBODY1C_##decl, __VA_ARGS__)
#define STRUCTBODY1C_int int ,
#define STRUCTBODY1C_char char ,
#define STRUCTBODY1C_float float ,
#define STRUCTBODY1C_pint pint ,
#define STRUCTBODY1C_pchar pchar ,
#define STRUCTBODY1C_pfloat pfloat ,
#define STRUCTBODY1C_pvoid pvoid ,
#define STRUCTBODY1C(pr, decl, ...) STRUCTBODY1Ci(pr, decl,  __VA_ARGS__)
#define STRUCTBODY1Ci(pr, type, ident, ...) type pr##ident; STRUCTBODY2(pr,  __VA_ARGS__)
#define STRUCTBODY2(pr, decl, ...) STRUCTBODY2B(pr, STRUCTBODY2A_##decl,  __VA_ARGS__) 
#define STRUCTBODY2A_     
#define STRUCTBODY2A_int     decl , int
#define STRUCTBODY2A_char    decl , char
#define STRUCTBODY2A_float    decl , float
#define STRUCTBODY2A_pint    decl , pint
#define STRUCTBODY2A_pchar    decl , pchar
#define STRUCTBODY2A_pfloat    decl , pfloat
#define STRUCTBODY2A_pvoid    decl , pvoid
#define STRUCTBODY2A_pass pass ,
#define STRUCTBODY2A_decl decl ,
#define STRUCTBODY2B(pr, tag, ...)  STRUCTBODY2Bi(pr, tag, __VA_ARGS__)
#define STRUCTBODY2Bi(pr, tag, ...) STRUCTBODY2B_##tag(pr, __VA_ARGS__)
#define STRUCTBODY2B_(...)
#define STRUCTBODY2B_pass(pr, decl, ...) STRUCTBODY2C(pr, STRUCTBODY2C_##decl, __VA_ARGS__)
#define STRUCTBODY2B_decl(pr, decl, ...) STRUCTBODY2C(pr, STRUCTBODY2C_##decl, __VA_ARGS__)
#define STRUCTBODY2C_int int ,
#define STRUCTBODY2C_char char ,
#define STRUCTBODY2C_float float ,
#define STRUCTBODY2C_pint pint ,
#define STRUCTBODY2C_pchar pchar ,
#define STRUCTBODY2C_pfloat pfloat ,
#define STRUCTBODY2C_pvoid pvoid ,
#define STRUCTBODY2C(pr, decl, ...) STRUCTBODY2Ci(pr, decl,  __VA_ARGS__)
#define STRUCTBODY2Ci(pr, type, ident, ...) type pr##ident; STRUCTBODY3(pr, pass, __VA_ARGS__)
#define STRUCTBODY3(...)
*/

#define PRARGLIST(pr, ...) PRARGLIST1(pr, __VA_ARGS__)
#define PRARGLIST1(pr, decl, ...) PRARGLIST1B(pr, PRARGLIST1A_##decl,  __VA_ARGS__) 
#define PRARGLIST1A_     
#define PRARGLIST1A_pass pass ,
#define PRARGLIST1A_decl decl ,
#define PRARGLIST1B(pr, tag, ...)  PRARGLIST1Bi(pr, tag, __VA_ARGS__)
#define PRARGLIST1Bi(pr, tag, ...) PRARGLIST1B_##tag(pr, __VA_ARGS__)
#define PRARGLIST1B_(...)
#define PRARGLIST1B_pass(pr, decl, ...) PRARGLIST1C(pr, pass, PRARGLIST1C_##decl, __VA_ARGS__)
#define PRARGLIST1B_decl(pr, decl, ...) PRARGLIST1C(pr, decl, PRARGLIST1C_##decl, __VA_ARGS__)
#define PRARGLIST1C_int int ,
#define PRARGLIST1C_char char ,
#define PRARGLIST1C_float float ,
#define PRARGLIST1C_pint pint ,
#define PRARGLIST1C_pchar pchar ,
#define PRARGLIST1C_ppchar ppchar ,
#define PRARGLIST1C_pfloat pfloat ,
#define PRARGLIST1C_pvoid pvoid ,
#define PRARGLIST1C(pr, tag, decl, ...) PRARGLIST1Ci(pr, tag, decl,  __VA_ARGS__)
#define PRARGLIST1Ci(pr, tag, type, ident, ...) tag type pr##ident PRARGLIST2(pr, tag, __VA_ARGS__)
#define PRARGLIST2(pr, lasttag, decl, ...) PRARGLIST2B(pr, lasttag, PRARGLIST2A_##decl,  __VA_ARGS__) 
#define PRARGLIST2A_     
#define PRARGLIST2A_int     chain , int
#define PRARGLIST2A_char    chain , char
#define PRARGLIST2A_float    chain , float
#define PRARGLIST2A_pint    chain , pint
#define PRARGLIST2A_pchar    chain , pchar
#define PRARGLIST2A_ppchar   chain , ppchar
#define PRARGLIST2A_pfloat    chain , pfloat
#define PRARGLIST2A_pvoid    chain , pvoid
#define PRARGLIST2A_pass pass ,
#define PRARGLIST2A_decl decl ,
#define PRARGLIST2B(pr, lasttag, tag, ...)  PRARGLIST2Bi(pr, lasttag, tag, __VA_ARGS__)
#define PRARGLIST2Bi(pr, lasttag, tag, ...) PRARGLIST2B_##tag(pr, lasttag, __VA_ARGS__)
#define PRARGLIST2B_(...)
#define PRARGLIST2B_chain(pr, lasttag, decl, ...) PRARGLIST2C(pr, lasttag, PRARGLIST2C_##decl, __VA_ARGS__)
#define PRARGLIST2B_pass(pr, lasttag, decl, ...)  PRARGLIST2C(pr, pass, PRARGLIST2C_##decl, __VA_ARGS__)
#define PRARGLIST2B_decl(pr, lasttag, decl, ...)  PRARGLIST2C(pr, decl, PRARGLIST2C_##decl, __VA_ARGS__)
#define PRARGLIST2C_int int ,
#define PRARGLIST2C_char char ,
#define PRARGLIST2C_float float ,
#define PRARGLIST2C_pint pint ,
#define PRARGLIST2C_pchar pchar ,
#define PRARGLIST2C_ppchar ppchar ,
#define PRARGLIST2C_pfloat pfloat ,
#define PRARGLIST2C_pvoid pvoid ,
#define PRARGLIST2C(pr, tag, decl, ...) PRARGLIST2Ci(pr, tag, decl,  __VA_ARGS__)
#define PRARGLIST2Ci(pr, tag, type, ident, ...) , tag type pr##ident PRARGLIST3(pr, tag, __VA_ARGS__)
#define PRARGLIST3(...)


#define FNV(...)           \
	FNVDECLS(__VA_ARGS__), \
    FNVIDCLS(__VA_ARGS__), \
	FNVSAVES(__VA_ARGS__), \
	(FNVPARS(__VA_ARGS__)),\
	(FNVARGS(__VA_ARGS__)) //


#define FNVDECLS(...) FNVDECLS1(__VA_ARGS__)
#define FNVDECLS1(decl, ...) FNVDECLS1B(FNVDECLS1A_##decl,  __VA_ARGS__) 
#define FNVDECLS1A_
#define FNVDECLS1A_pass pass ,
#define FNVDECLS1A_decl decl ,
#define FNVDECLS1B(tag, ...)  FNVDECLS1Bi(tag, __VA_ARGS__)
#define FNVDECLS1Bi(tag, ...) FNVDECLS1B_##tag(__VA_ARGS__)
#define FNVDECLS1B_(...)
#define FNVDECLS1B_pass(decl, ...) FNVDECLS2(pass, __VA_ARGS__)
#define FNVDECLS1B_decl(vdecl, ...) vdecl; FNVDECLS2(decl, __VA_ARGS__)
#define FNVDECLS2(lasttag, decl, ...) FNVDECLS2B(lasttag, FNVDECLS2A_##decl,  __VA_ARGS__) 
#define FNVDECLS2A_
#define FNVDECLS2A_int     chain , int
#define FNVDECLS2A_char    chain , char
#define FNVDECLS2A_float    chain , float
#define FNVDECLS2A_pint    chain , pint
#define FNVDECLS2A_pchar    chain , pchar
#define FNVDECLS2A_ppchar   chain , ppchar
#define FNVDECLS2A_pfloat    chain , pfloat
#define FNVDECLS2A_pvoid    chain , pvoid
#define FNVDECLS2A_pass pass ,
#define FNVDECLS2A_decl decl ,
#define FNVDECLS2B(lasttag, tag, ...)  FNVDECLS2Bi(lasttag, tag, __VA_ARGS__)
#define FNVDECLS2Bi(lasttag, tag, ...) FNVDECLS2B_##tag(lasttag, __VA_ARGS__)
#define FNVDECLS2B_(...)
#define FNVDECLS2B_chain(lasttag, decl, ...) FNVDECLS2B_##lasttag(lasttag, decl, __VA_ARGS__)
#define FNVDECLS2B_pass(lasttag, decl, ...) FNVDECLS3(pass, __VA_ARGS__)
#define FNVDECLS2B_decl(lasttag, vdecl, ...) vdecl; FNVDECLS3(decl, __VA_ARGS__)
#define FNVDECLS3(lasttag, decl, ...) FNVDECLS3B(lasttag, FNVDECLS3A_##decl,  __VA_ARGS__) 
#define FNVDECLS3A_
#define FNVDECLS3A_int     chain , int
#define FNVDECLS3A_char    chain , char
#define FNVDECLS3A_float    chain , float
#define FNVDECLS3A_pint    chain , pint
#define FNVDECLS3A_pchar    chain , pchar
#define FNVDECLS3A_ppchar    chain , ppchar
#define FNVDECLS3A_pfloat    chain , pfloat
#define FNVDECLS3A_pvoid    chain , pvoid
#define FNVDECLS3A_pass pass ,
#define FNVDECLS3A_decl decl ,
#define FNVDECLS3B(lasttag, tag, ...)  FNVDECLS3Bi(lasttag, tag, __VA_ARGS__)
#define FNVDECLS3Bi(lasttag, tag, ...) FNVDECLS3B_##tag(lasttag, __VA_ARGS__)
#define FNVDECLS3B_(...)
#define FNVDECLS3B_chain(lasttag, decl, ...) FNVDECLS3B_##lasttag(lasttag, decl, __VA_ARGS__)
#define FNVDECLS3B_pass(lasttag, decl, ...) FNVDECLS4(pass, __VA_ARGS__)
#define FNVDECLS3B_decl(lasttag, vdecl, ...) vdecl; FNVDECLS4(decl, __VA_ARGS__)
#define FNVDECLS4(lasttag, decl, ...) FNVDECLS4B(lasttag, FNVDECLS4A_##decl,  __VA_ARGS__) 
#define FNVDECLS4A_
#define FNVDECLS4A_int     chain , int
#define FNVDECLS4A_char    chain , char
#define FNVDECLS4A_float    chain , float
#define FNVDECLS4A_pint    chain , pint
#define FNVDECLS4A_pchar    chain , pchar
#define FNVDEVLS4A_ppchar   chain , ppchar
#define FNVDECLS4A_pfloat    chain , pfloat
#define FNVDECLS4A_pvoid    chain , pvoid
#define FNVDECLS4A_pass pass ,
#define FNVDECLS4A_decl decl ,
#define FNVDECLS4B(lasttag, tag, ...)  FNVDECLS4Bi(lasttag, tag, __VA_ARGS__)
#define FNVDECLS4Bi(lasttag, tag, ...) FNVDECLS4B_##tag(lasttag, __VA_ARGS__)
#define FNVDECLS4B_(...)
#define FNVDECLS4B_chain(lasttag, decl, ...) FNVDECLS4B_##lasttag(lasttag, decl, __VA_ARGS__)
#define FNVDECLS4B_pass(lasttag, decl, ...) FNVDECLS5(pass, __VA_ARGS__)
#define FNVDECLS4B_decl(lasttag, vdecl, ...) vdecl; FNVDECLS5(decl, __VA_ARGS__)
#define FNVDECLS5(...)


/*
#define FNVDECLS(case, ...)  \
        FNVDECLS1_##case(__VA_ARGS__);
#define FNVDECLS1_(...)
#define FNVDECLS1_pass(decl, ...) FNVDECLS2(__VA_ARGS__)
#define FNVDECLS1_decl(decl, ...) decl FNVDECLS2(__VA_ARGS__)
#define FNVDECLS2(case, ...) FNVDECLS2_##case(__VA_ARGS__)
#define FNVDECLS2_(...)
#define FNVDECLS2_pass(decl, ...) 
#define FNVDECLS2_decl(decl, ...) decl*/

#define FNVIDCLS(...) FNVIDCLS1(__VA_ARGS__)
#define FNVIDCLS1(decl, ...) FNVIDCLS1B(FNVIDCLS1A_##decl,  __VA_ARGS__) 
#define FNVIDCLS1A_
#define FNVIDCLS1A_pass pass ,
#define FNVIDCLS1A_decl decl ,
#define FNVIDCLS1B(tag, ...)  FNVIDCLS1Bi(tag, __VA_ARGS__)
#define FNVIDCLS1Bi(tag, ...) FNVIDCLS1B_##tag(__VA_ARGS__)
#define FNVIDCLS1B_(...)
#define FNVIDCLS1B_pass(decl, ...) decl = *deltype##decl##_; FNVIDCLS2(pass, __VA_ARGS__)
#define FNVIDCLS1B_decl(vdecl, ...) vdecl = *deltype##vdecl##_; FNVIDCLS2(decl, __VA_ARGS__)
#define FNVIDCLS2(lasttag, decl, ...) FNVIDCLS2B(lasttag, FNVIDCLS2A_##decl,  __VA_ARGS__) 
#define FNVIDCLS2A_
#define FNVIDCLS2A_int     chain , int
#define FNVIDCLS2A_char    chain , char
#define FNVIDCLS2A_float    chain , float
#define FNVIDCLS2A_pint    chain , pint
#define FNVIDCLS2A_pchar    chain , pchar
#define FNVIDCLS2A_ppchar   chain , ppchar
#define FNVIDCLS2A_pfloat    chain , pfloat
#define FNVIDCLS2A_pvoid    chain , pvoid
#define FNVIDCLS2A_pass pass ,
#define FNVIDCLS2A_decl decl ,
#define FNVIDCLS2B(lasttag, tag, ...)  FNVIDCLS2Bi(lasttag, tag, __VA_ARGS__)
#define FNVIDCLS2Bi(lasttag, tag, ...) FNVIDCLS2B_##tag(lasttag, __VA_ARGS__)
#define FNVIDCLS2B_(...)
#define FNVIDCLS2B_chain(lasttag, decl, ...) FNVIDCLS2B_##lasttag(lasttag, decl, __VA_ARGS__)
#define FNVIDCLS2B_pass(lasttag, decl, ...) decl = *deltype##decl##_; FNVIDCLS3(pass, __VA_ARGS__)
#define FNVIDCLS2B_decl(lasttag, vdecl, ...) vdecl = *deltype##vdecl##_; FNVIDCLS3(decl, __VA_ARGS__)
#define FNVIDCLS3(lasttag, decl, ...) FNVIDCLS3B(lasttag, FNVIDCLS3A_##decl,  __VA_ARGS__) 
#define FNVIDCLS3A_
#define FNVIDCLS3A_int     chain , int
#define FNVIDCLS3A_char    chain , char
#define FNVIDCLS3A_float    chain , float
#define FNVIDCLS3A_pint    chain , pint
#define FNVIDCLS3A_pchar    chain , pchar
#define FNVIDCLS3A_ppchar   chain , ppchar
#define FNVIDCLS3A_pfloat    chain , pfloat
#define FNVIDCLS3A_pvoid    chain , pvoid
#define FNVIDCLS3A_pass pass ,
#define FNVIDCLS3A_decl decl ,
#define FNVIDCLS3B(lasttag, tag, ...)  FNVIDCLS3Bi(lasttag, tag, __VA_ARGS__)
#define FNVIDCLS3Bi(lasttag, tag, ...) FNVIDCLS3B_##tag(lasttag, __VA_ARGS__)
#define FNVIDCLS3B_(...)
#define FNVIDCLS3B_chain(lasttag, decl, ...) FNVIDCLS3B_##lasttag(lasttag, decl, __VA_ARGS__)
#define FNVIDCLS3B_pass(lasttag, decl, ...) decl = *deltype##decl##_; FNVIDCLS4(pass, __VA_ARGS__)
#define FNVIDCLS3B_decl(lasttag, vdecl, ...) vdecl = *deltype##vdecl##_; FNVIDCLS4(decl, __VA_ARGS__)
#define FNVIDCLS4(lasttag, decl, ...) FNVIDCLS4B(lasttag, FNVIDCLS4A_##decl,  __VA_ARGS__) 
#define FNVIDCLS4A_
#define FNVIDCLS4A_int     chain , int
#define FNVIDCLS4A_char    chain , char
#define FNVIDCLS4A_float    chain , float
#define FNVIDCLS4A_pint    chain , pint
#define FNVIDCLS4A_pchar    chain , pchar
#define FNVIDCLS4A_ppchar   chain , ppchar
#define FNVIDCLS4A_pfloat    chain , pfloat
#define FNVIDCLS4A_pvoid    chain , pvoid
#define FNVIDCLS4A_pass pass ,
#define FNVIDCLS4A_decl decl ,
#define FNVIDCLS4B(lasttag, tag, ...)  FNVIDCLS4Bi(lasttag, tag, __VA_ARGS__)
#define FNVIDCLS4Bi(lasttag, tag, ...) FNVIDCLS4B_##tag(lasttag, __VA_ARGS__)
#define FNVIDCLS4B_(...)
#define FNVIDCLS4B_chain(lasttag, decl, ...) FNVIDCLS4B_##lasttag(lasttag, decl, __VA_ARGS__)
#define FNVIDCLS4B_pass(lasttag, decl, ...) decl = *deltype##decl##_; FNVIDCLS5(pass, __VA_ARGS__)
#define FNVIDCLS4B_decl(lasttag, vdecl, ...) vdecl = *deltype##vdecl##_; FNVIDCLS5(decl, __VA_ARGS__)
#define FNVIDCLS5(...)

/*
#define FNVIDCLS(...) FNVIDCLS1(__VA_ARGS__)
#define FNVIDCLS1(decl, ...) FNVIDCLS1_##case(__VA_ARGS__)
#define FNVIDCLS1_(...)
#define FNVIDCLS1_pass(decl, ...) decl = *deltype##decl##_; FNVIDCLS2(__VA_ARGS__)
#define FNVIDCLS1_decl(decl, ...) decl = *deltype##decl##_; FNVIDCLS2(__VA_ARGS__)
#define FNVIDCLS2(case, ...) FNVIDCLS2_##case(__VA_ARGS__)
#define FNVIDCLS2_(...)
#define FNVIDCLS2_pass(decl, ...) decl = *deltype##decl##_; 
#define FNVIDCLS2_decl(decl, ...) decl = *deltype##decl##_;
*/


#define FNVSAVES(...) FNVSAVES1(__VA_ARGS__)
#define FNVSAVES1(decl, ...) FNVSAVES1B(FNVSAVES1A_##decl,  __VA_ARGS__) 
#define FNVSAVES1A_
#define FNVSAVES1A_pass pass ,
#define FNVSAVES1A_decl decl ,
#define FNVSAVES1B(tag, ...)  FNVSAVES1Bi(tag, __VA_ARGS__)
#define FNVSAVES1Bi(tag, ...) FNVSAVES1B_##tag(__VA_ARGS__)
#define FNVSAVES1B_(...)
#define FNVSAVES1B_pass(decl, ...) *deltype##decl##_ = deltype##decl; FNVSAVES2(pass, __VA_ARGS__)
#define FNVSAVES1B_decl(vdecl, ...) *deltype##vdecl##_ = deltype##vdecl; FNVSAVES2(decl, __VA_ARGS__)
#define FNVSAVES2(lasttag, decl, ...) FNVSAVES2B(lasttag, FNVSAVES2A_##decl,  __VA_ARGS__) 
#define FNVSAVES2A_
#define FNVSAVES2A_int     chain , int
#define FNVSAVES2A_char    chain , char
#define FNVSAVES2A_float    chain , float
#define FNVSAVES2A_pint    chain , pint
#define FNVSAVES2A_pchar    chain , pchar
#define FNVSAVES2A_ppchar   chain , ppchar
#define FNVSAVES2A_pfloat    chain , pfloat
#define FNVSAVES2A_pvoid    chain , pvoid
#define FNVSAVES2A_pass pass ,
#define FNVSAVES2A_decl decl ,
#define FNVSAVES2B(lasttag, tag, ...)  FNVSAVES2Bi(lasttag, tag, __VA_ARGS__)
#define FNVSAVES2Bi(lasttag, tag, ...) FNVSAVES2B_##tag(lasttag, __VA_ARGS__)
#define FNVSAVES2B_(...)
#define FNVSAVES2B_chain(lasttag, decl, ...) FNVSAVES2B_##lasttag(lasttag, decl, __VA_ARGS__)
#define FNVSAVES2B_pass(lasttag, decl, ...) \
    *deltype##decl##_ = deltype##decl; FNVSAVES3(pass, __VA_ARGS__)
#define FNVSAVES2B_decl(lasttag, vdecl, ...) \
    *deltype##vdecl##_ = deltype##vdecl; FNVSAVES3(decl, __VA_ARGS__)
#define FNVSAVES3(lasttag, decl, ...) FNVSAVES3B(lasttag, FNVSAVES3A_##decl,  __VA_ARGS__) 
#define FNVSAVES3A_
#define FNVSAVES3A_int     chain , int
#define FNVSAVES3A_char    chain , char
#define FNVSAVES3A_float    chain , float
#define FNVSAVES3A_pint    chain , pint
#define FNVSAVES3A_pchar    chain , pchar
#define FNVSAVES3A_ppchar   chain , ppchar
#define FNVSAVES3A_pfloat    chain , pfloat
#define FNVSAVES3A_pvoid    chain , pvoid
#define FNVSAVES3A_pass pass ,
#define FNVSAVES3A_decl decl ,
#define FNVSAVES3B(lasttag, tag, ...)  FNVSAVES3Bi(lasttag, tag, __VA_ARGS__)
#define FNVSAVES3Bi(lasttag, tag, ...) FNVSAVES3B_##tag(lasttag, __VA_ARGS__)
#define FNVSAVES3B_(...)
#define FNVSAVES3B_chain(lasttag, decl, ...) FNVSAVES3B_##lasttag(lasttag, decl, __VA_ARGS__)
#define FNVSAVES3B_pass(lasttag, decl, ...) \
    *deltype##decl##_ = deltype##decl; FNVSAVES4(pass, __VA_ARGS__)
#define FNVSAVES3B_decl(lasttag, vdecl, ...) \
    *deltype##vdecl##_ = deltype##vdecl; FNVSAVES4(decl, __VA_ARGS__)
#define FNVSAVES4(lasttag, decl, ...) FNVSAVES4B(lasttag, FNVSAVES4A_##decl,  __VA_ARGS__) 
#define FNVSAVES4A_
#define FNVSAVES4A_int     chain , int
#define FNVSAVES4A_char    chain , char
#define FNVSAVES4A_float    chain , float
#define FNVSAVES4A_pint    chain , pint
#define FNVSAVES4A_pchar    chain , pchar
#define FNVSAVES4A_ppchar    chain , ppchar
#define FNVSAVES4A_pfloat    chain , pfloat
#define FNVSAVES4A_pvoid    chain , pvoid
#define FNVSAVES4A_pass pass ,
#define FNVSAVES4A_decl decl ,
#define FNVSAVES4B(lasttag, tag, ...)  FNVSAVES4Bi(lasttag, tag, __VA_ARGS__)
#define FNVSAVES4Bi(lasttag, tag, ...) FNVSAVES4B_##tag(lasttag, __VA_ARGS__)
#define FNVSAVES4B_(...)
#define FNVSAVES4B_chain(lasttag, decl, ...) FNVSAVES4B_##lasttag(lasttag, decl, __VA_ARGS__)
#define FNVSAVES4B_pass(lasttag, decl, ...) \
    *deltype##decl##_ = deltype##decl; FNVSAVES5(pass, __VA_ARGS__)
#define FNVSAVES4B_decl(lasttag, vdecl, ...) \
    *deltype##vdecl##_ = deltype##vdecl; FNVSAVES5(decl, __VA_ARGS__)
#define FNVSAVES5(...)

/*
#define FNVSAVES(...) FNVSAVES1(__VA_ARGS__)
#define FNVSAVES1(case, ...) FNVSAVES1_##case(__VA_ARGS__)
#define FNVSAVES1_(...)
#define FNVSAVES1_pass(decl, ...) *deltype##decl##_ = deltype##decl; FNVSAVES2(__VA_ARGS__)
#define FNVSAVES1_decl(decl, ...) *deltype##decl##_ = deltype##decl; FNVSAVES2(__VA_ARGS__)
#define FNVSAVES2(case, ...) FNVSAVES2_##case(__VA_ARGS__)
#define FNVSAVES2_(...)
#define FNVSAVES2_pass(decl, ...) *deltype##decl##_ = deltype##decl;
#define FNVSAVES2_decl(decl, ...) *deltype##decl##_ = deltype##decl;
*/

#define COMMA ,

#define FNVPARS(...) FNVPARS1(__VA_ARGS__)
#define FNVPARS1(decl, ...) FNVPARS1B(FNVPARS1A_##decl,  __VA_ARGS__) 
#define FNVPARS1A_
#define FNVPARS1A_pass pass ,
#define FNVPARS1A_decl decl ,
#define FNVPARS1B(tag, ...)  FNVPARS1Bi(tag, __VA_ARGS__)
#define FNVPARS1Bi(tag, ...) FNVPARS1B_##tag(__VA_ARGS__)
#define FNVPARS1B_(...)
#define FNVPARS1B_pass(decl, ...) FNVPTRTYPE##decl##_ FNVPARS2(pass, __VA_ARGS__)
#define FNVPARS1B_decl(vdecl, ...) FNVPTRTYPE##vdecl##_ FNVPARS2(decl, __VA_ARGS__)
#define FNVPARS2(lasttag, decl, ...) FNVPARS2B(lasttag, FNVPARS2A_##decl,  __VA_ARGS__) 
#define FNVPARS2A_
#define FNVPARS2A_int     chain , int
#define FNVPARS2A_char    chain , char
#define FNVPARS2A_float    chain , float
#define FNVPARS2A_pint    chain , pint
#define FNVPARS2A_pchar    chain , pchar
#define FNVPARS2A_ppchar   chain , ppchar
#define FNVPARS2A_pfloat    chain , pfloat
#define FNVPARS2A_pvoid    chain , pvoid
#define FNVPARS2A_pass pass ,
#define FNVPARS2A_decl decl ,
#define FNVPARS2B(lasttag, tag, ...)  FNVPARS2Bi(lasttag, tag, __VA_ARGS__)
#define FNVPARS2Bi(lasttag, tag, ...) FNVPARS2B_##tag(lasttag, __VA_ARGS__)
#define FNVPARS2B_(...)
#define FNVPARS2B_chain(lasttag, decl, ...) FNVPARS2B_##lasttag(lasttag, decl, __VA_ARGS__)
#define FNVPARS2B_pass(lasttag, decl, ...) , FNVPTRTYPE##decl##_ FNVPARS3(pass, __VA_ARGS__)
#define FNVPARS2B_decl(lasttag, vdecl, ...) , FNVPTRTYPE##vdecl##_ FNVPARS3(decl, __VA_ARGS__)
#define FNVPARS3(lasttag, decl, ...) FNVPARS3B(lasttag, FNVPARS3A_##decl,  __VA_ARGS__) 
#define FNVPARS3A_
#define FNVPARS3A_int     chain , int
#define FNVPARS3A_char    chain , char
#define FNVPARS3A_float    chain , float
#define FNVPARS3A_pint    chain , pint
#define FNVPARS3A_pchar    chain , pchar
#define FNVPARS3A_ppchar    chain , ppchar
#define FNVPARS3A_pfloat    chain , pfloat
#define FNVPARS3A_pvoid    chain , pvoid
#define FNVPARS3A_pass pass ,
#define FNVPARS3A_decl decl ,
#define FNVPARS3B(lasttag, tag, ...)  FNVPARS3Bi(lasttag, tag, __VA_ARGS__)
#define FNVPARS3Bi(lasttag, tag, ...) FNVPARS3B_##tag(lasttag, __VA_ARGS__)
#define FNVPARS3B_(...)
#define FNVPARS3B_chain(lasttag, decl, ...) FNVPARS3B_##lasttag(lasttag, decl, __VA_ARGS__)
#define FNVPARS3B_pass(lasttag, decl, ...) , FNVPTRTYPE##decl##_ FNVPARS4(pass, __VA_ARGS__)
#define FNVPARS3B_decl(lasttag, vdecl, ...) , FNVPTRTYPE##vdecl##_ FNVPARS4(decl, __VA_ARGS__)
#define FNVPARS4(lasttag, decl, ...) FNVPARS4B(lasttag, FNVPARS4A_##decl,  __VA_ARGS__) 
#define FNVPARS4A_
#define FNVPARS4A_int     chain , int
#define FNVPARS4A_char    chain , char
#define FNVPARS4A_float    chain , float
#define FNVPARS4A_pint    chain , pint
#define FNVPARS4A_pchar    chain , pchar
#define FNVPARS4A_ppchar   chain , ppchar
#define FNVPARS4A_pfloat    chain , pfloat
#define FNVPARS4A_pvoid    chain , pvoid
#define FNVPARS4A_pass pass ,
#define FNVPARS4A_decl decl ,
#define FNVPARS4B(lasttag, tag, ...)  FNVPARS4Bi(lasttag, tag, __VA_ARGS__)
#define FNVPARS4Bi(lasttag, tag, ...) FNVPARS4B_##tag(lasttag, __VA_ARGS__)
#define FNVPARS4B_(...)
#define FNVPARS4B_chain(lasttag, decl, ...) FNVPARS4B_##lasttag(lasttag, decl, __VA_ARGS__)
#define FNVPARS4B_pass(lasttag, decl, ...) , FNVPTRTYPE##decl##_ FNVPARS5(pass, __VA_ARGS__)
#define FNVPARS4B_decl(lasttag, vdecl, ...) , FNVPTRTYPE##vdecl##_ FNVPARS5(decl, __VA_ARGS__)
#define FNVPARS5(...)

/*
#define FNVPARS(...) FNVPARS1(__VA_ARGS__)
#define FNVPARS1(case, ...) FNVPARS1_##case(__VA_ARGS__)
#define FNVPARS1_(...)
#define FNVPARS1_pass(decl, ...) FNVPTRTYPE##decl##_ FNVPARS2(__VA_ARGS__) 
#define FNVPARS1_decl(decl, ...) FNVPTRTYPE##decl##_ FNVPARS2(__VA_ARGS__)
#define FNVPARS2(case, ...) FNVPARS2_##case(__VA_ARGS__)
#define FNVPARS2_(...)
#define FNVPARS2_pass(decl, ...) , FNVPTRTYPE##decl##_
#define FNVPARS2_decl(decl, ...) , FNVPTRTYPE##decl##_
*/

#define FNVARGS(...) FNVARGS1(__VA_ARGS__)
#define FNVARGS1(decl, ...) FNVARGS1B(FNVARGS1A_##decl,  __VA_ARGS__) 
#define FNVARGS1A_
#define FNVARGS1A_pass pass ,
#define FNVARGS1A_decl decl ,
#define FNVARGS1B(tag, ...)  FNVARGS1Bi(tag, __VA_ARGS__)
#define FNVARGS1Bi(tag, ...) FNVARGS1B_##tag(__VA_ARGS__)
#define FNVARGS1B_(...)
#define FNVARGS1B_pass(decl, ...) &deltype##decl FNVARGS2(pass, __VA_ARGS__)
#define FNVARGS1B_decl(vdecl, ...) &deltype##vdecl FNVARGS2(decl, __VA_ARGS__)
#define FNVARGS2(lasttag, decl, ...) FNVARGS2B(lasttag, FNVARGS2A_##decl,  __VA_ARGS__) 
#define FNVARGS2A_
#define FNVARGS2A_int     chain , int
#define FNVARGS2A_char    chain , char
#define FNVARGS2A_float    chain , float
#define FNVARGS2A_pint    chain , pint
#define FNVARGS2A_pchar    chain , pchar
#define FNVARGS2A_ppchar   chain , ppchar
#define FNVARGS2A_pfloat    chain , pfloat
#define FNVARGS2A_pvoid    chain , pvoid
#define FNVARGS2A_pass pass ,
#define FNVARGS2A_decl decl ,
#define FNVARGS2B(lasttag, tag, ...)  FNVARGS2Bi(lasttag, tag, __VA_ARGS__)
#define FNVARGS2Bi(lasttag, tag, ...) FNVARGS2B_##tag(lasttag, __VA_ARGS__)
#define FNVARGS2B_(...)
#define FNVARGS2B_chain(lasttag, decl, ...) FNVARGS2B_##lasttag(lasttag, decl, __VA_ARGS__)
#define FNVARGS2B_pass(lasttag, decl, ...) , &deltype##decl FNVARGS3(pass, __VA_ARGS__)
#define FNVARGS2B_decl(lasttag, vdecl, ...) , &deltype##vdecl FNVARGS3(decl, __VA_ARGS__)
#define FNVARGS3(lasttag, decl, ...) FNVARGS3B(lasttag, FNVARGS3A_##decl,  __VA_ARGS__) 
#define FNVARGS3A_
#define FNVARGS3A_int     chain , int
#define FNVARGS3A_char    chain , char
#define FNVARGS3A_float    chain , float
#define FNVARGS3A_pint    chain , pint
#define FNVARGS3A_pchar    chain , pchar
#define FNVARGS3A_ppchar    chain , ppchar
#define FNVARGS3A_pfloat    chain , pfloat
#define FNVARGS3A_pvoid    chain , pvoid
#define FNVARGS3A_pass pass ,
#define FNVARGS3A_decl decl ,
#define FNVARGS3B(lasttag, tag, ...)  FNVARGS3Bi(lasttag, tag, __VA_ARGS__)
#define FNVARGS3Bi(lasttag, tag, ...) FNVARGS3B_##tag(lasttag, __VA_ARGS__)
#define FNVARGS3B_(...)
#define FNVARGS3B_chain(lasttag, decl, ...) FNVARGS3B_##lasttag(lasttag, decl, __VA_ARGS__)
#define FNVARGS3B_pass(lasttag, decl, ...) , &deltype##decl FNVARGS4(pass, __VA_ARGS__)
#define FNVARGS3B_decl(lasttag, vdecl, ...) , &deltype##vdecl FNVARGS4(decl, __VA_ARGS__)
#define FNVARGS4(lasttag, decl, ...) FNVARGS4B(lasttag, FNVARGS4A_##decl,  __VA_ARGS__) 
#define FNVARGS4A_
#define FNVARGS4A_int     chain , int
#define FNVARGS4A_char    chain , char
#define FNVARGS4A_float    chain , float
#define FNVARGS4A_pint    chain , pint
#define FNVARGS4A_pchar    chain , pchar
#define FNVARGS4A_ppchar    chain , ppchar
#define FNVARGS4A_pfloat    chain , pfloat
#define FNVARGS4A_pvoid    chain , pvoid
#define FNVARGS4A_pass pass ,
#define FNVARGS4A_decl decl ,
#define FNVARGS4B(lasttag, tag, ...)  FNVARGS4Bi(lasttag, tag, __VA_ARGS__)
#define FNVARGS4Bi(lasttag, tag, ...) FNVARGS4B_##tag(lasttag, __VA_ARGS__)
#define FNVARGS4B_(...)
#define FNVARGS4B_chain(lasttag, decl, ...) FNVARGS4B_##lasttag(lasttag, decl, __VA_ARGS__)
#define FNVARGS4B_pass(lasttag, decl, ...) , &deltype##decl FNVARGS5(pass, __VA_ARGS__)
#define FNVARGS4B_decl(lasttag, vdecl, ...) , &deltype##vdecl FNVARGS5(decl, __VA_ARGS__)
#define FNVARGS5(...)

/*
#define FNVARGS(...) FNVARGS1(__VA_ARGS__)
#define FNVARGS1(case, ...) FNVARGS1_##case(__VA_ARGS__)
#define FNVARGS1_(...)
#define FNVARGS1_pass(decl, ...) &deltype##decl FNVARGS2(__VA_ARGS__) 
#define FNVARGS1_decl(decl, ...) &deltype##decl FNVARGS2(__VA_ARGS__)
#define FNVARGS2(case, ...) FNVARGS2_##case(__VA_ARGS__)
#define FNVARGS2_(...)
#define FNVARGS2_pass(decl, ...) , &deltype##decl 
#define FNVARGS2_decl(decl, ...) , &deltype##decl
*/

#define FNBLOCK2(              fnv, code)                  \
        FNBLOCK2A(__COUNTER__, APPLYMACRO(FNV, fnv), code) //
#define FNBLOCK2A(identfrag,   fnv, code) \
        FNBLOCK2C(identfrag,   fnv, code) //  
#define FNBLOCK2B(decls, idecls, saves, pars, args, code)              \
        FNBLOCK2D(__COUNTER__, decls, idecls, saves, pars, args, code) //
#define FNBLOCK2D(identfrag,   decls, idecls, saves, pars, args, code) \
        FNBLOCK2C(identfrag,   decls, idecls, saves, pars, args, code) //
#define FNBLOCK2C(identfrag,   decls, idecls, saves, pars, args, code) \
	decls;                                            \
	void anonfn##identfrag pars                       \
	{                                                 \
	    {                                             \
	        idecls;                                   \
	        code;                                     \
	        saves;                                    \
	    }                                             \
	}                                                 \
	anonfn##identfrag args ;                          //

#define fnc fctA FNV
#define fctA fct1 fct2
#define fct1 FNBLOCK2B
#define fct2 (
#define fbl_end )
#define end_fbl )
#define end_ )

inline
void debugmacro()
{


#define coords int x, int y

EVALECHO
(

loctag
/*
stm STRUCTBODY(c, coords)
fnc (pass PRARGLIST(c, coords)),
    stm x = y = 1;
end // warning this keyword changed in the meantime
stm ed(x);
*/
/*
fct FNV (decl, int defstrchrnul),
    int a = 0;
    stm defstrchrnul = 0;
    iff !ctxt->interactive
    thn defstrchrnul = 0;
    stm
	stm printfflush("prooted? [y] ");
    chr *answer = mgetline("");
    stm
	iff !strncmp(answer, "y", 1)
    thn defstrchrnul = 0;
    iff !strncmp(answer, "n", 1)
    thn defstrchrnul = 1;
    stm defstrchrnul = 0;
end // warning this keyword changed in the meantime
//*/

)

	
}
//*/

#define testoptresultnonempty "nonempty"
#define testoptresult "empty"
#define testopt(...) testoptresult##__VA_OPT__(nonempty)
#define rest(a, ...) begin##__VA_ARGS__
#define first(a, ...)
#define testva(...) first(__VA_ARGS__) rest(__VA_ARGS__)

#define vardup(...) __VA_ARGS__ __VA_ARGS__ __VA_ARGS__

#define pair 1, 2
#define printfpairdirect(a, b) printf("%d, %d\n", a, b);
#define printfpair(x) printfpairdirect(x)
#define tmpcmd printfpair(pair)

inline
void tmpmain()
{
	tmpcmd;
}

#undef pair
#undef printfpairdirect
#undef printfpair
#undef tmpcmd

#endif
