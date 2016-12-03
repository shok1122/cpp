#pragma once

#include <typedef.h>
#include <getopt.h>
#include <string>

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
	virtual std::string& toString(std::string& a_str) = 0;
	std::string& help(std::string& a_str) const;

	COptBase(const char* ac_pcharOptName, HasArg a_eHasArg, const char* ac_pcharDescription);
	virtual ~COptBase();
};
