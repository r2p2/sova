#include "args.h"
#include "cmdln.h"

#include "capture/storage/stdout.h"
#include "capture/storage/file.h"
#include "capture/ctrl.h"

#include <boost/asio.hpp>

#include <string>
#include <stdlib.h> // getenv

int main(int argc, char *argv[])
{
	Args args;

	CmdLn parser(argc, argv);
	parser.parse_into(args);

	if (args.print_help or not args.cap_mode)
	{
		std::cout << parser.help() << std::endl;
		return 1;
	}

	boost::asio::io_service io_service;

	if (args.cap_mode)
	{
		auto log = std::make_shared<capture::storage::File>(
				std::string(getenv("HOME")) + "/.sova/cap", "main");

		capture::Ctrl ctrl(io_service, *log);

		ctrl.start();
	}

	io_service.run();

	return 0;
}
