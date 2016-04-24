#include "stdout.h"

#include "entry.h"

#include <iostream>

namespace capture
{

namespace storage
{

StdOut::StdOut()
: Log()
{}

void StdOut::append(Entry const& entry)
{
	std::cout << _fmt_time(entry.tp)
			<< ": " << entry.window_name
			<< ", " << entry.window_class
			<< ", " << entry.window_command
			<< ", " << entry.window_idle << std::endl;
}

std::string StdOut::_fmt_time(std::chrono::system_clock::time_point const& tp)
{
	auto timestamp = std::chrono::system_clock::to_time_t(tp);
	auto localts = std::localtime(&timestamp);
	char cstr[128];
	std::strftime(cstr, sizeof(cstr), "%c", localts);

	return std::string(cstr);
}

} // namespace storage

} // namespace capture
