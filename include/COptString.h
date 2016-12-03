#pragma once

#include <typedef.h>
#include <COptBase.h>

#include <string>

class COptString : public COptBase
{
public:
	const char* mc_pcharVal;

	virtual void decode(const char* a_optarg);
	virtual std::string& toString(std::string& a_str);

	COptString(const char* ac_pcharOptName, const char* ac_pcharDescription);
	virtual ~COptString();
};
