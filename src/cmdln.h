#pragma once

#include <boost/program_options.hpp>

namespace po = boost::program_options;

struct Args
{
	bool print_help;
	bool print_version;

	bool cap_mode;

	bool daemonize;
};

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
