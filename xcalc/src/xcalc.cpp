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
static u32 opt_val = 0;
static u8 opt_size = 1;
static u32 opt_width_data = 0;
static u32 opt_height_data = 0;
static u32 opt_width_start_calc = 0;
static u32 opt_height_start_calc = 0;
static u32 opt_width_end_calc = 0;
static u32 opt_height_end_calc = 0;
static FILE* opt_in_file = NULL;
static FILE* opt_out_file = stdout;

static void help()
{
	fprintf(stderr,
			"usage: %s [OPTION...] [FILE]\n"
			"[OPTION]\n"
			"    --mode <ARG>           計算モードを指定\n"
			"                           ARG: add, sub, and, or\n"
			"    --val  <ARG>           計算に使用する値\n"
			"    --size <ARG>           計算単位サイズ\n"
			"                           ARG: 1, 2, 4\n"
			"    --area <ARG1> <ARG2>   入力データエリアARG1に対してARG2エリアを計算\n"
			"                           ARG1: <WIDTH>x<HEIGHT>\n"
			"                           ARG2: <WIDTH>x<HEIGHT> *start:0\n"
			"    --help                 ヘルプを表示\n"
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
	OPTTYPE_SIZE,
	OPTTYPE_AREA,
	OPTTYPE_HELP,
};

struct option long_options[] = 
{
	{ "mode", required_argument, &long_opt, OPTTYPE_MODE },
	{ "val",  required_argument, &long_opt, OPTTYPE_VAL  },
	{ "size", required_argument, &long_opt, OPTTYPE_SIZE },
	{ "area", required_argument, &long_opt, OPTTYPE_AREA },
	{ "help", no_argument,       &long_opt, OPTTYPE_HELP },
	{ 0, 0, 0, 0 }
};

static bool decode_longopts(int a_long_opt)
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
		case OPTTYPE_SIZE:
		{
			opt_size = atoi(optarg);
			if (1 != opt_size && 2 != opt_size && 4 != opt_size)
			{
				return false;
			}
		}
			break;
		case OPTTYPE_AREA:
		{
			char* token1 = strtok(optarg, ",");
			char* token2 = strtok(NULL, ",");
			char* token3 = strtok(NULL, ",");

			opt_width_data = atoi(strtok(token1, "x"));
			opt_height_data = atoi(strtok(NULL, "x"));

			opt_width_start_calc = atoi(strtok(token2, "-"));
			opt_height_start_calc = atoi(strtok(NULL, "-"));

			opt_width_end_calc = atoi(strtok(token3, "-"));
			opt_height_end_calc = atoi(strtok(NULL, "-"));
		}
			break;
		default:
		{
			help();
		}
			break;
	}

	return true;
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
				if (false == decode_longopts(long_opt))
				{
					return false;
				}
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

static u32 decode(u8 size, u32 i, u8* a_pbuffer)
{
	u32 retval;
	switch (size)
	{
		case 1:
		{
			u8* pTmp = (u8*) &(a_pbuffer[i]);
			retval = *pTmp;
		}
			break;
		case 2:
		{
			u16* pTmp = (u16*) &(a_pbuffer[i]);
			retval = *pTmp;
		}
			break;
		case 4:
		{
			u32* pTmp = (u32*) &(a_pbuffer[i]);
			retval = *pTmp;
		}
			break;
	}

	return retval;
}

static void encode(u8 size, u32 data, u32 i, u8* a_pbuffer)
{
	switch (size)
	{
		case 1:
		{
			u8* pTmp = (u8*) &(a_pbuffer[i]);
			*pTmp = data;
		}
			break;
		case 2:
		{
			u16* pTmp = (u16*) &(a_pbuffer[i]);
			*pTmp = data;
		}
			break;
		case 4:
		{
			u32* pTmp = (u32*) &(a_pbuffer[i]);
			*pTmp = data;
		}
			break;
	}
}

static void calc(u32 a_size, u8* a_pbuffer)
{
	for (u32 i = opt_height_start_calc; i < opt_height_start_calc + opt_height_end_calc; i++)
	{
		for (u32 j = opt_width_start_calc; j < opt_width_start_calc + opt_width_end_calc; j++)
		{
			u32 offset = ((i * opt_width_data) + j) * opt_size;
			u32 data = decode(opt_size, offset, a_pbuffer);

			switch (opt_calc_mode)
			{
				case calc_add:
				{
					data += opt_val;
				}
					break;
				case calc_sub:
				{
					data -= opt_val;
				}
					break;
				case calc_and:
				{
					data &= opt_val;
				}
					break;
				case calc_or:
				{
					data |= opt_val;
				}
					break;
				default:
					break;
			}

			encode(opt_size, data, offset, a_pbuffer);
		}
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

	if (false == getargs(argc, argv))
	{
		help();
		return 1;
	}
	if (false == check_opt()) return 1;

	run();

	return 0;
}
