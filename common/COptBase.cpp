#include <typedef.h>
#include <COptBase.h>

#include <stdio.h>
#include <string.h>

COptBase::COptBase(const char* ac_pcharOptName, HasArg a_eHasArg, const char* ac_pcharDescription):
	mc_pcharOptName(ac_pcharOptName),
	mc_pcharDescription(ac_pcharDescription),
	mc_eHasArg(a_eHasArg)
{
	// do nothing
}

COptBase::~COptBase()
{
	// do nothing
}

char* COptBase::help(char* a_pcharBuf, u32 a_u32BufSize) const
{
	char pcharOptName[16];
	memset(pcharOptName, ' ', sizeof(pcharOptName));

	snprintf(pcharOptName, sizeof(pcharOptName), "--%s %s",
		mc_pcharOptName,
		(HasArg::NO_ARGUMENT == mc_eHasArg) ? "" : "<ARG>");

	pcharOptName[strlen(pcharOptName)] = ' ';
	pcharOptName[sizeof(pcharOptName)] = 0;

	snprintf(a_pcharBuf, a_u32BufSize, "    %s %s\n", pcharOptName, mc_pcharDescription);

	return a_pcharBuf;
}
