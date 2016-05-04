#pragma once

#include <boost/program_options.hpp>

namespace po = boost::program_options;

struct Args;

class CmdLn
{
public:
	CmdLn(int argc, char* argv[]);

	std::string help() const;

	void parse_into(Args& args);

private:
	po::options_description _desc;

	int                     _argc;
	char**                  _argv;
};
