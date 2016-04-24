#include "capture/storage/stdout.h"
#include "capture/ctrl.h"

#include <boost/asio.hpp>

int main(int argc, char *argv[])
{
	boost::asio::io_service io_service;

	auto log = std::make_shared<capture::storage::StdOut>();

	capture::Ctrl ctrl(io_service, *log);

	ctrl.start();

	io_service.run();

	return 0;
}
