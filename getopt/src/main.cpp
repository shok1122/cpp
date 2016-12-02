#include <stdio.h>
#include <CGetOpt.h>
#include <COptUint32.h>

#include <getopt.h>

static const char* sc_pcharUsage =
	"usage: getopt [OPTION]\n"
	"test getopt\n";
static const char* sc_pcharHelp =
	"show this help\n";

static COptUint32 s_cOptAaa(10, "aaa", "aaa is decimal value");
static COptUint32 s_cOptBbb(16, "bbb", "bbb is hex value");
static COptUint32 s_cOptCcc(10, "ccc", "ccc is decimal value");

int main(int argc, char** argv)
{
	CGetOpt cGetOpt(sc_pcharUsage, sc_pcharHelp);

	cGetOpt.add(&s_cOptAaa);
	cGetOpt.add(&s_cOptBbb);
	cGetOpt.add(&s_cOptCcc);

	cGetOpt.getopt(argc, argv);

	return 0;
}
