#pragma once

#include <typedef.h>
#include <COptBase.h>

class COptHelp : public COptBase
{
public:
	bool m_bEnable;

	virtual void decode(const char* a_optarg);
	virtual char* toString(char* a_pcharBuffer, u32 a_u32BufferSize);

	COptHelp(const char* ac_pcharDescription);
	virtual ~COptHelp();
};
