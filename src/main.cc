#include "capture/storage/stdout.h"
#include "capture/storage/file.h"
#include "capture/ctrl.h"

#include <boost/asio.hpp>

#include <string>
#include <stdlib.h> // getenv

int main(int argc, char *argv[])
{
	boost::asio::io_service io_service;

	auto log = std::make_shared<capture::storage::File>(
			std::string(getenv("HOME")) + "/.sova/cap", "main");

	capture::Ctrl ctrl(io_service, *log);

	ctrl.start();

	io_service.run();

	return 0;
}
