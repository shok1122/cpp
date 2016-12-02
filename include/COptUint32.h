#pragma once

#include <typedef.h>
#include <COptBase.h>

class COptUint32 : public COptBase
{
public:
	u32 m_u32Val;

	virtual void decode(const char* a_optarg);
	virtual char* toString(char* a_pcharBuffer, u32 a_u32BufferSize);

	COptUint32(u8 a_u8Base, const char* ac_pcharOptName, const char* ac_pcharDescription);
	virtual ~COptUint32();

private:
	u8 m_u8Base = 0;
};
