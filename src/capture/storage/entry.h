#pragma once

#include <string>
#include <chrono>

namespace capture
{

namespace storage
{

using namespace std::chrono;

struct Entry
{
	system_clock::time_point  tp;
	std::string               window_name;
	std::string               window_class;
	std::string               window_command;
	unsigned int              window_idle;
};

}

} // namespace capture
