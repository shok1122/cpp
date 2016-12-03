#include <COptBoolean.h>
#include <COptBase.h>

#include <typedef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

COptBoolean::COptBoolean(const char* ac_pcharOptName, const char* ac_pcharDescription):
		COptBase(ac_pcharOptName, COptBase::HasArg::NO_ARGUMENT, ac_pcharDescription),
		m_bEnable(false)
{
}

COptBoolean::~COptBoolean()
{
}

void COptBoolean::decode(const char* a_optarg)
{
	m_bEnable = true;
}

std::string& COptBoolean::toString(std::string& a_str)
{
	a_str.append("--");
	a_str.append(mc_pcharOptName);
	a_str.append("=");
	a_str.append((true == m_bEnable) ? "enable" : "disable");
	a_str.append("\n");

	return a_str;
}
