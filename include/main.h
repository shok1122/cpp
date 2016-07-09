#include <typedef.h>
#include <libgen.h>

static const char* PROG_NAME;

static void prepare_main(int argc, char** argv)
{
	PROG_NAME = basename(argv[0]);
}
