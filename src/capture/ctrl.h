#pragma once

#include "storage/entry.h"
#include "x/xadapter.h"

#include <chrono>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>


using namespace boost::asio;

namespace capture
{

namespace storage
{

class Log;

} // namespace storage

class Ctrl
{
public:
	Ctrl(io_service& service, storage::Log& log);
	~Ctrl();

	void start();
	void stop();

private:
	void _schedule();
	void _capture_timeout(boost::system::error_code const& error);
	void _store_capture();

private:
	bool                 _running;

	io_service&          _service;
	steady_timer         _timer;

	std::chrono::seconds _capture_interval;

	storage::Log&        _log;
	x::XAdapter          _x;

	storage::Entry       _current_entry;
};

} // namespace capture
