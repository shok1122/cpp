#pragma once

#include <typedef.h>
#include <COptBase.h>

#include <string>

class COptHelp : public COptBase
{
public:
	bool m_bEnable;

	virtual void decode(const char* a_optarg);
	virtual std::string& toString(std::string& a_str);

	COptHelp(const char* ac_pcharDescription);
	virtual ~COptHelp();
};
