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

char* COptUint32::toString(char* a_pcharBuffer, u32 a_u32BufferSize)
{
	u32 u32Size = a_u32BufferSize - strlen(a_pcharBuffer);
	snprintf(a_pcharBuffer, u32Size, "--%s=%ld\n", mc_pcharOptName, m_u32Val);
	return a_pcharBuffer;
}
