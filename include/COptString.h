#pragma once

#include <typedef.h>
#include <COptBase.h>

class COptString : public COptBase
{
public:
	const char* mc_pcharVal;

	virtual void decode(const char* a_optarg);
	virtual char* toString(char* a_pcharBuffer, u32 a_u32BufferSize);

	COptString(const char* ac_pcharOptName, const char* ac_pcharDescription);
	virtual ~COptString();
};
