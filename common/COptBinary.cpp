#include <COptBinary.h>
#include <COptBase.h>

#include <typedef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

COptBinary::COptBinary(const char* ac_pcharOptName, const char* ac_pcharDescription):
		COptBase(ac_pcharOptName, COptBase::HasArg::NO_ARGUMENT, ac_pcharDescription),
		m_bEnable(false)
{
}

COptBinary::~COptBinary()
{
}

void COptBinary::decode(const char* a_optarg)
{
	m_bEnable = true;
}

std::string& COptBinary::toString(std::string& a_str)
{
	a_str.append("--");
	a_str.append(mc_pcharOptName);
	a_str.append("=");
	a_str.append((true == m_bEnable) ? "enable" : "disable");
	a_str.append("\n");

	return a_str;
}
