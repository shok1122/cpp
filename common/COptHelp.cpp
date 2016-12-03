#include <COptHelp.h>
#include <COptBase.h>

#include <typedef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

COptHelp::COptHelp(const char* ac_pcharDescription):
		COptBase("help", COptBase::HasArg::NO_ARGUMENT, ac_pcharDescription),
		m_bEnable(false) 
{
}

COptHelp::~COptHelp()
{
}

void COptHelp::decode(const char* a_optarg)
{
	m_bEnable = true;
}

std::string& COptHelp::toString(std::string& a_str)
{
	// do nothing
	return a_str;
}
