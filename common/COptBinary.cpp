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

char* COptBinary::toString(char* a_pcharBuffer, u32 a_u32BufferSize)
{
	u32 u32Size = a_u32BufferSize - strlen(a_pcharBuffer);
	snprintf(a_pcharBuffer, u32Size, "--%s=%s\n",
			mc_pcharOptName,
			(true == m_bEnable) ? "enable" : "disable");
	return a_pcharBuffer;
}
