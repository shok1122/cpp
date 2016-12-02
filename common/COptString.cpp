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

char* COptString::toString(char* a_pcharBuffer, u32 a_u32BufferSize)
{
	u32 u32Size = a_u32BufferSize - strlen(a_pcharBuffer);
	snprintf(a_pcharBuffer, u32Size, "--%s=%s\n", mc_pcharOptName, mc_pcharVal);
	return a_pcharBuffer;
}
