#include "ctrl.h"

#include "storage/log.h"

#include <boost/bind.hpp>

namespace capture
{

Ctrl::Ctrl(io_service& service, storage::Log& log)
: _running(false)
, _service(service)
, _timer(_service)
, _capture_interval(1)
, _log(log)
, _x()
, _current_entry()
{
}

Ctrl::~Ctrl()
{
	stop();
}

void Ctrl::start()
{
	_x.connect();

	if (not _x.is_connected())
		return;

	_running = true;
	_schedule();
}

void Ctrl::stop()
{
	// TODO implement
}

void Ctrl::_schedule()
{
	_timer.expires_from_now(_capture_interval);
	_timer.async_wait(
			boost::bind(&Ctrl::_capture_timeout, this, placeholders::error));
}

void Ctrl::_capture_timeout(boost::system::error_code const& error)
{
	if (error or not _running)
		return;

	_schedule();

	_current_entry.tp = std::chrono::system_clock::now();
	x::WindowProperties window = _x.focus_window_properties();

	_current_entry.window_name = window.name;
	_current_entry.window_class = window.xclass;
	_current_entry.window_command = window.command;
	_current_entry.window_idle = window.idle;

	_store_capture();
}

void Ctrl::_store_capture()
{
	_log.append(_current_entry);
}

} // namespace capture
