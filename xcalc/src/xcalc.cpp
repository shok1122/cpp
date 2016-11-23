#include <typedef.h>
#include <main.h>
#include <log.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

static enum CalcMode
{
	calc_nop = 0,
	calc_add,
	calc_sub,
	calc_and,
	calc_or,
} opt_calc_mode;

static FILE* opt_in_file = NULL;
static FILE* opt_out_file = stdout;
static u32 opt_val = 0;

static void help()
{
	fprintf(stderr,
			"usage: %s [OPTION...] [FILE]\n"
			"[OPTION]\n"
			"    --mode    計算モードを指定\n"
			"              add, sub, and, or\n"
			"    --val     計算に使用する値\n"
			"    --help    ヘルプを表示\n"
			"    \n"
			, PROG_NAME
			);
}

static CalcMode calc_mode(const char* m_value)
{
	if (0 == strcmp(m_value, "add"))
	{
		return calc_add;
	}
	else if (0 == strcmp(m_value, "sub"))
	{
		return calc_sub;
	}
	else if (0 == strcmp(m_value, "and"))
	{
		return calc_and;
	}
	else if (0 == strcmp(m_value, "or"))
	{
		return calc_or;
	}
	else
	{
		// do nothing
	}

	return calc_nop;
}

int long_opt;
enum OPTTYPE
{
	OPTTYPE_MODE = 1,
	OPTTYPE_VAL,
	OPTTYPE_HELP,
};

struct option long_options[] = 
{
	{ "mode", required_argument, &long_opt, OPTTYPE_MODE },
	{ "val",  required_argument, &long_opt, OPTTYPE_VAL  },
	{ "help", no_argument,       &long_opt, OPTTYPE_HELP },
	{ 0, 0, 0, 0 }
};

static void decode_longopts(int a_long_opt)
{
	switch (a_long_opt)
	{
		case OPTTYPE_MODE:
		{
			opt_calc_mode = calc_mode(optarg);
		}
			break;
		case OPTTYPE_VAL:
		{
			char* endptr;
			opt_val = strtol(optarg, &endptr, 16);
		}
			break;
		default:
		{
			help();
		}
			break;
	}
}

static bool getargs(int argc, char** argv)
{
	int opt;
	int long_opt_index;
	while ((opt = getopt_long(argc, argv, "h", long_options, &long_opt_index)) != -1)
	{
		switch (opt)
		{
			case 0:
				decode_longopts(long_opt);
				break;
			case 'h':
				help();
				break;
			default:
				break;
		}
	}

	opt_in_file = fopen(argv[optind++], "rb");

	return true;
}

static bool check_opt()
{
	if (NULL == opt_in_file)
	{
		return false;
	}

	return true;
}

static void calc(u32 a_size, u8* a_pbuffer)
{
	switch (opt_calc_mode)
	{
		case calc_add:
		{
			for (u32 i = 0; i < a_size; i++)
			{
				a_pbuffer[i] += opt_val;
			}
		}
			break;
		case calc_sub:
		{
			for (u32 i = 0; i < a_size; i++)
			{
				a_pbuffer[i] -= opt_val;
			}
		}
			break;
		case calc_and:
		{
			for (u32 i = 0; i < a_size; i++)
			{
				a_pbuffer[i] &= opt_val;
			}
		}
			break;
		case calc_or:
		{
			for (u32 i = 0; i < a_size; i++)
			{
				a_pbuffer[i] |= opt_val;
			}
		}
			break;
		default:
			break;
	}
}

static void run()
{
	static const u32 buffer_size = 256;
	u8 buffer[buffer_size];

	u32 read_size_file = 0;
	while (0 < (read_size_file = fread(buffer, 1, buffer_size, opt_in_file)))
	{
		calc(read_size_file, buffer);

		fwrite(buffer, 1, read_size_file, opt_out_file);
	}

	fflush(opt_out_file);
}

int main(int argc, char** argv)
{
	prepare_main(argc, argv);

	if (false == getargs(argc, argv)) return 1;
	if (false == check_opt()) return 1;

	run();

	return 0;
}
