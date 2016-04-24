#pragma once

#include "log.h"

#include <string>
#include <chrono>

namespace capture
{

namespace storage
{

class StdOut : public Log
{
public:
	StdOut();
	virtual ~StdOut() = default;

	virtual void append(Entry const& entry);

private:
	static std::string _fmt_time(
			std::chrono::system_clock::time_point const& tp);
};

} // namespace storage

} // namespace capture
