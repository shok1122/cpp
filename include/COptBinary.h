#pragma once

#include <typedef.h>
#include <COptBase.h>

#include <string>

class COptBinary : public COptBase
{
public:
	bool m_bEnable;

	virtual void decode(const char* a_optarg);
	virtual std::string& toString(std::string& a_str);

	COptBinary(const char* ac_pcharOptName, const char* ac_pcharDescription);
	virtual ~COptBinary();
};
