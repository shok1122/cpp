#pragma once

#include <typedef.h>
#include <COptBase.h>
#include <COptHelp.h>

#include <vector>

class CGetOpt
{
public:
	CGetOpt(const char* ac_pcharOptUsage, const char* ac_pcharOptHelpDescription);
	virtual ~CGetOpt();

	void add(COptBase* a_pcOptBase);
	bool getopt(int a_argc, char** a_argv);
	char* toString(char* a_pcharBuffer, u32 a_u32Size);
	void help() const;

private:

	COptHelp m_cOptHelp;
	const char* mc_pcharOptUsage;
	int m_intFlag;

	std::vector<COptBase*> m_vectorOpts;

	void makeLongOpt(struct option* a_options, u32 a_u32OptNum);
	bool decode(const char* a_name, char* a_optarg);

};
