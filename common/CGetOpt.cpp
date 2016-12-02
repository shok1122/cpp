#include <CGetOpt.h>
#include <COptUint32.h>

#include <typedef.h>
#include <getopt.h>

#include <stdio.h>
#include <string.h>

CGetOpt::CGetOpt(const char* ac_pcharOptUsage, const char* ac_pcharOptHelpDescription):
	m_cOptHelp(ac_pcharOptHelpDescription),
	mc_pcharOptUsage(ac_pcharOptUsage),
	m_intFlag(-1)
{
}

CGetOpt::~CGetOpt()
{
}

void CGetOpt::makeLongOpt(struct option* a_options, u32 a_u32OptionNum)
{
	u32 u32Index;
	for (u32Index = 0; u32Index < m_vectorOpts.size(); u32Index++)
	{
		COptBase* pcOptBase = m_vectorOpts[u32Index];
		a_options[u32Index].name = pcOptBase->mc_pcharOptName;
		a_options[u32Index].has_arg = pcOptBase->mc_eHasArg;
		a_options[u32Index].flag = &m_intFlag;
		a_options[u32Index].val = u32Index;
	}

	memset(&(a_options[u32Index]), 0, sizeof(option));
}

bool CGetOpt::decode(const char* a_name, char* a_optarg)
{
	bool isFound = false;
	COptBase* pcOptBase;
	for (u32 u32Index = 0; u32Index < m_vectorOpts.size(); u32Index++)
	{
		pcOptBase = m_vectorOpts[u32Index];
		if (0 == strcmp(a_name, pcOptBase->mc_pcharOptName))
		{
			isFound = true;
			break;
		}
	}
	if (false == isFound)
	{
		return false;
	}

	pcOptBase->decode(a_optarg);

	return true;
}

char* CGetOpt::toString(char* a_pcharBuffer, u32 a_u32Size)
{
	memset(a_pcharBuffer, 0, a_u32Size);
	for (u32 u32Index = 0; u32Index < m_vectorOpts.size(); u32Index++)
	{
		COptBase* pcOptBase = m_vectorOpts[u32Index];
		snprintf(a_pcharBuffer, strlen(a_pcharBuffer), "%s", pcOptBase->toString(a_pcharBuffer, a_u32Size));
	}

	return a_pcharBuffer;
}

void CGetOpt::add(COptBase* a_pcOptBase)
{
	m_vectorOpts.push_back(a_pcOptBase);
}

bool CGetOpt::getopt(int a_argc, char** a_argv)
{
	add(&m_cOptHelp);

	u32 u32OptNum = m_vectorOpts.size();
	struct option options[u32OptNum + 1];
	makeLongOpt(options, u32OptNum);
#if 1
	int opt;
	int intOptIndex;

	while ((opt = getopt_long(a_argc, a_argv, "h", options, &intOptIndex)) != -1)
	{
		switch (opt)
		{
		case 0:
			if (false == decode(options[intOptIndex].name, optarg))
			{
				return false;
			}
				break;
		case 'h':
			help();
			break;
		default:
			break;
		}
	}
#endif

	if (true == m_cOptHelp.m_bEnable)
	{
		help();
		return false;
	}
	else
	{
		char pcharBuffer[256];
		memset(pcharBuffer, 0, sizeof(pcharBuffer));
		fprintf(stderr, "%s", toString(pcharBuffer, sizeof(pcharBuffer)));
	}

	return true;
}

void CGetOpt::help() const
{
	fprintf(stderr, "%s", mc_pcharOptUsage);
	fprintf(stderr, "[OPTION]\n");

	char pcharBuf[256];
	for (u32 u32Index = 0; u32Index < m_vectorOpts.size(); u32Index++)
	{
		COptBase* pcOptBase = m_vectorOpts[u32Index];
		fprintf(stderr, "%s", pcOptBase->help(pcharBuf, 256));
	}
}
