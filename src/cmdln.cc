#include "cmdln.h"

#include "args.h"

CmdLn::CmdLn(int argc, char* argv[])
: _desc("Description")
, _argc(argc)
, _argv(argv)
{
	_desc.add_options()
		("version,v", "print the current version")
		("help,h", "print this help message")
		("capture,c", "start in capture mode")
		("daemonize,d", "daemonize application after start");
}

std::string CmdLn::help() const
{
	std::stringstream ss;
	ss << _desc;

	return ss.str();
}

void CmdLn::parse_into(Args& args)
{
	try
	{
		po::variables_map vm;
		po::store(
			po::parse_command_line(
				  _argc
				, _argv
				, _desc), vm);
		po::notify(vm);

		if (vm.count("help"))
			args.print_help = true;

		if (vm.count("version"))
			args.print_version = true;

		if (vm.count("capture"))
			args.cap_mode = true;

		if (vm.count("daemonize"))
			args.daemonize = true;
	}
	catch (std::exception& e)
	{
		args.print_help = true;
	}
}

