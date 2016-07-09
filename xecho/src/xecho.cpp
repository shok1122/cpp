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

void get_input(u8** stdout_data, u32* data_len)
{
	if (NULL != opt_stdin_data)
	{
		*data_len = opt_stdin_data_len / 2;
		*stdout_data = (u8*) malloc(*data_len);
		u8 hex_strings_len = strlen(opt_stdin_data);
		for (u8 i = 0; i < hex_strings_len; i+=2)
		{
			sscanf(&(opt_stdin_data[i]), "%02X", (unsigned int*) &((*stdout_data)[i/2]));
		}
	}
}

int main(int argc, char** argv)
{
	prepare_main(argc, argv);
	getargs(argc, argv);

	u8* stdout_data;
	u32 data_len = 0;
	get_input(&stdout_data, &data_len);

	for(u8 i = 0; i < opt_duplication_size; i++)
	{
		fwrite(stdout_data, 1, data_len, stdout);
	}

	fflush(stdout);
	free(stdout_data);

	return 0;
}
