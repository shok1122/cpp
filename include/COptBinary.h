#pragma once

#include <typedef.h>
#include <COptBase.h>

class COptBinary : public COptBase
{
public:
	bool m_bEnable;

	virtual void decode(const char* a_optarg);
	virtual char* toString(char* a_pcharBuffer, u32 a_u32BufferSize);

	COptBinary(const char* ac_pcharOptName, const char* ac_pcharDescription);
	virtual ~COptBinary();
};
