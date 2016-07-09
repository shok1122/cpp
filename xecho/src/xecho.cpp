#include <typedef.h>
#include <main.h>
#include <log.h>

#include <stdlib.h>
#include <string.h>
#include <getopt.h>

static u8 opt_duplication_size = 1; // default: 1 byte
static char* opt_stdin_data = nullptr;
static u32 opt_stdin_data_len;

static void getargs(int argc, char** argv)
{
	int opt;
	while (-1 != (opt = getopt(argc, argv, "l:")))
	{
		switch (opt)
		{
			case 'l':
			{
				u32 l = atol(optarg);
				opt_duplication_size = (0xFF < l) ? 0xFF : l;
				break;
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
				opt_stdin_data = argv[optind++];
				opt_stdin_data_len = strlen(opt_stdin_data);
				break;
			default:
				break;
		}
		c++;
	}
}

bool get_input(u8** stdout_data, u32* stdin_data_len)
{
	if (NULL == opt_stdin_data)
	{
		*stdout_data = (u8*) malloc(32);
		u8* stdin_buffer = *stdout_data;
		while (true)
		{
			char tmp[4];
			memset(tmp, 0, sizeof(tmp));
			u32 c = fread(stdin_buffer, 1, 4, stdin);
			if (0 == c)
			{
				break;
			}
			*stdin_data_len += c;
		}
		if (0 == feof(stdin))
		{
			LOGOUT("error: fread(stdin)");
			return false;
		}
	}
	else
	{
		*stdin_data_len = opt_stdin_data_len / 2;
		*stdout_data = (u8*) malloc(*stdin_data_len);
		u8 hex_strings_len = strlen(opt_stdin_data);
		for (u8 i = 0; i < hex_strings_len; i+=2)
		{
			sscanf(&(opt_stdin_data[i]), "%02X", (unsigned int*) &((*stdout_data)[i/2]));
		}
	}

	return true;
}

int main(int argc, char** argv)
{
	prepare_main(argc, argv);
	getargs(argc, argv);

	u8* stdout_data;
	u32 data_len = 0;
	if (false == get_input(&stdout_data, &data_len))
	{
		return 10;
	}

	for(u8 i = 0; i < opt_duplication_size; i++)
	{
		fwrite(stdout_data, 1, data_len, stdout);
	}

	free(stdout_data);

	return 0;
}
