#include <COptString.h>
#include <COptBase.h>

#include <typedef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

COptString::COptString(const char* ac_pcharOptName, const char* ac_pcharDescription):
		COptBase(ac_pcharOptName, COptBase::HasArg::REQUIRED_ARGUMENT, ac_pcharDescription),
		mc_pcharVal(nullptr)
{
}

COptString::~COptString()
{
}

void COptString::decode(const char* a_optarg)
{
	mc_pcharVal = a_optarg;
}

std::string& COptString::toString(std::string& a_str)
{
	a_str.append("--");
	a_str.append(mc_pcharOptName);
	a_str.append("=");
	a_str.append((nullptr == mc_pcharVal) ? "(null)" : mc_pcharVal);
	a_str.append("\n");

	return a_str;
}
