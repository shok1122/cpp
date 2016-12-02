#pragma once

#include <typedef.h>
#include <getopt.h>

class COptBase
{
public:
	const char* mc_pcharOptName;
	const char* mc_pcharDescription;
	enum HasArg
	{
		REQUIRED_ARGUMENT = required_argument,
		OPTIONAL_ARGUMENT = optional_argument,
		NO_ARGUMENT = no_argument,
	} ;
	const HasArg mc_eHasArg;

	virtual void decode(const char* a_optarg) = 0;
	virtual char* toString(char* a_pcharBuffer, u32 a_u32BufferSize) = 0;
	char* help(char* a_pcharBuf, u32 a_u32BufSize) const;

	COptBase(const char* ac_pcharOptName, HasArg a_eHasArg, const char* ac_pcharDescription);
	virtual ~COptBase();
};
