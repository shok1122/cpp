#include <COptUint32.h>
#include <COptBase.h>

#include <typedef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

COptUint32::COptUint32(u8 a_u8Base,
		const char* ac_pcharOptName, const char* ac_pcharDescription):
		COptBase(ac_pcharOptName, COptBase::HasArg::REQUIRED_ARGUMENT, ac_pcharDescription),
		m_u8Base(a_u8Base)
{
}

COptUint32::~COptUint32()
{
}

void COptUint32::decode(const char* a_optarg)
{
	char* pcharEnd;
	m_u32Val = (u32) strtol(a_optarg, &pcharEnd, m_u8Base);
}

std::string& COptUint32::toString(std::string& a_str)
{
	a_str.append("--");
	a_str.append(mc_pcharOptName);
	a_str.append("=");
	a_str += std::to_string(m_u32Val);
	a_str.append("\n");
	return a_str;
}
