#pragma once

namespace capture
{

namespace storage
{

class Entry;

class Log
{
public:
	virtual ~Log() = default;

	virtual void append(Entry const& entry) = 0;
};

} // namespace storage

} // namespace capture
