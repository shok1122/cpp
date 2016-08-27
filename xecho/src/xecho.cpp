#include <typedef.h>
#include <main.h>
#include <log.h>

#include <stdlib.h>
#include <string.h>
#include <getopt.h>

static u32 opt_duplication_size = 1; // default: 1 byte
static char* opt_stdin_data = nullptr;
static u32 opt_stdin_data_len;
static enum MODE { eDUPLICATE, eCOUNTUP, eCOUNTDOWN } opt_mode = eDUPLICATE;
static long opt_amount = 1;
static FILE* opt_file = NULL;
static FILE* opt_out_file = stdout;

static void help()
{
	fputs(
			"usage: %s [OPTION...] [HEX_STRING] [OUT_FILE]\n"
			"指定されたバイナリデータからオプションに応じて生成したバイナリデータを標準出力に出力します．\n"
			"\n"
			"[OPTION...]\n"
			"    -l NUM    入力データのサイズをNUM倍にする．\n"
			"    -m MODE   NUM倍時にMODEに応じた演算を加える（MUST: -l）\n"
			"              MODE: countup-NUM, countdown-NUM それぞれNUM分インクリメント，デクリメントを行う．\n"
			"              NUMを省略した場合，1が入力されたとして扱われる．\n"
			"    -f FILE   入力データにファイルを指定．\n"
			"    -h        ヘルプを表示．\n"
			"\n"
			"[HEX_STRING]\n"
			"    入力データ．16進数文字列で指定．\n"
			"    指定が無い場合，標準入力から受け付ける．\n"
			"\n"
			"[OUT_FILE]\n"
			"    出力ファイル名．\"-\"を指定すると標準出力に出力．\n"
			"\n"
			"使用例：\n"
			"    xecho -l 8 -m countup 0000 | xecho -l 2 | xecho -l 4 -m countup-16 > out.dat\n"
			"    [out.dat]\n"
			"    0000000 : 0000 0101 0202 0303 0404 0505 0606 0707\n"
			"    0000010 : 0000 0101 0202 0303 0404 0505 0606 0707\n"
			"    0000020 : 1010 1111 1212 1313 1414 1515 1616 1717\n"
			"    0000030 : 1010 1111 1212 1313 1414 1515 1616 1717\n"
			"    0000040 : 2020 2121 2222 2323 2424 2525 2626 2727\n"
			"    0000050 : 2020 2121 2222 2323 2424 2525 2626 2727\n"
			"    0000060 : 3030 3131 3232 3333 3434 3535 3636 3737\n"
			"    0000070 : 3030 3131 3232 3333 3434 3535 3636 3737\n"
			"    0000080 : \n"
			"\n", stderr);
}

static bool getargs(int argc, char** argv)
{
	int opt;
	while (-1 != (opt = getopt(argc, argv, "hl:m:f:")))
	{
		switch (opt)
		{
			case 'h':
			{
				help();
				return false;
			}
			case 'l':
			{
				u32 l = atol(optarg);
				opt_duplication_size = (0xffffffff < l) ? 0xffffffff : l;
				break;
			}
			case 'm':
			{
				if (0 == strcmp("duplicate", optarg))
				{
					opt_mode = eDUPLICATE;
				}
				else if ((strcmp("countup", optarg) <= 0) || (strcmp("countdown", optarg) <= 0))
				{
					char* mode = strtok(optarg, "-");
					char* amount = strtok(NULL, "-");
					if (NULL == mode) break;
					if (0 == strcmp("countup", mode))
					{
						opt_mode = eCOUNTUP;
						opt_amount = (NULL == amount) ? 1 : atol(amount);
					}
					else if (0 == strcmp("countdown", mode))
					{
						opt_mode = eCOUNTDOWN;
						opt_amount = (NULL == amount) ? (-1) : (-1) * atol(amount);
					}
				}
				else
				{
					opt_mode = eDUPLICATE;
				}
				break;
			}
			case 'f':
			{
				opt_file = fopen(optarg, "rb");
			}
			default:
			{
				break;
			}
		}
	}

	u8 c = 0;
	while (optind < argc)
	{
		switch (c)
		{
			case 0:
			{
				opt_stdin_data_len = strlen(argv[optind]);
				if (0 != opt_stdin_data_len%2)
				{
					opt_stdin_data = (char*) malloc(opt_stdin_data_len + 1 + 1);
					strcpy(opt_stdin_data, "0");
					strcat(opt_stdin_data, argv[optind]);
					opt_stdin_data_len++;
				}
				else
				{
					opt_stdin_data = (char*) malloc(opt_stdin_data_len + 1);
					strcpy(opt_stdin_data, argv[optind]);
				}
			}
				optind++;
				break;
			case 1:
			{
				char* path_outfile = argv[optind];
				if (0 == strcmp("-", path_outfile))
				{
					opt_out_file = stdout;
				}
				else
				{
					opt_out_file = fopen(path_outfile, "wb");
				}
			}
				optind++;
				break;
			default:
				break;
		}
		c++;
	}

	return true;
}

bool get_input(u8** stdout_data, u32* stdin_data_len)
{
	if (NULL == opt_stdin_data)
	{
		static const u32 memory_block_size = 256;
		u32 memory_block_num = 1;
		*stdout_data = (u8*) malloc(memory_block_size);
		u8* stdin_buffer = *stdout_data;
		FILE* fp = (NULL == opt_file) ? stdin : opt_file;
		while (true)
		{
			u32 memory_size = memory_block_size * memory_block_num;
			if (memory_size <= *stdin_data_len)
			{
				memory_size = memory_block_size * (++memory_block_num);
				*stdout_data = (u8*) realloc(
						*stdout_data,
						memory_size);
			}
			u32 c = fread(
					&(stdin_buffer[*stdin_data_len]),
					1, memory_size - *stdin_data_len,
					fp);
			if (0 == c)
			{
				break;
			}
			*stdin_data_len += c;
		}
		if (0 == feof(fp))
		{
			LOGOUT("error: fread(stdin)");
			return false;
		}

		if (stdin != fp)
		{
			fclose(fp);
		}
	}
	else
	{
		*stdin_data_len = opt_stdin_data_len / 2;
		*stdout_data = (u8*) malloc(*stdin_data_len);

		u32 index = 0;
		for (u8 i = opt_stdin_data_len; 0 < i; i-=2)
		{
			char* endptr;

			char pcharByteStr1[3] = {0};
			memcpy(pcharByteStr1, &(opt_stdin_data[i-2]), 2);
			long l = strtol(pcharByteStr1, &endptr, 16);

			(*stdout_data)[index++] = l;
		}
	}

	return true;
}

int main(int argc, char** argv)
{
	prepare_main(argc, argv);
	if (false == getargs(argc, argv)) return 1;

	u8* stdout_data;
	u32 data_len = 0;
	if (false == get_input(&stdout_data, &data_len))
	{
		return 10;
	}

	for(u32 i = 0; i < opt_duplication_size; i++)
	{
		if (eDUPLICATE == opt_mode)
		{
			// do nothing
		}
		else if (eCOUNTUP == opt_mode || eCOUNTDOWN == opt_mode)
		{
			for (u32 j = 0; j < data_len; j++)
			{
				if (0 < i) stdout_data[j] += opt_amount;
			}
		}
		fwrite(stdout_data, 1, data_len, opt_out_file);
	}

	fclose(opt_out_file);
	free(stdout_data);

	return 0;
}
