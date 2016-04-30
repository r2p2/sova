#include "file.h"

#include "entry.h"

#include <sstream>

namespace capture
{

namespace storage
{

File::File(std::string const& dir, std::string const& name)
: _dir(dir)
, _name(name)
, _file()
, _date()
{
}

File::~File()
{
}

void File::append(Entry const& entry)
{
	if (_has_date_changed())
		_change_file();

	_file << _fmt(entry) << std::endl;
}

bool File::_has_date_changed() const
{
	return _date != day_clock::local_day();
}

void File::_change_file()
{
	_date = day_clock::local_day();
	_file.open(_path(), std::ios::out | std::ios::app);
}

std::string File::_path() const
{
	std::stringstream ss;
	ss << _dir << "/"
		<< _date.year() << "_"
		<< _date.month() << "_"
		<< _date.day() << "_"
		<< _name << ".cap";
	return ss.str();
}

std::string File::_fmt(Entry const& entry) const
{
	std::stringstream ss;
	ss << "{ "
		<< "\"core\": { "
			<< "\"tp\":\"" << _fmt_time(entry.tp) << "\", "
			<< "\"wn\":\"" << entry.window_name << "\", "
			<< "\"wcl\":\"" << entry.window_class << "\", "
			<< "\"wcm\":\"" << entry.window_command << "\", "
			<< "\"wi\":" << entry.window_idle << "} }";

	return ss.str();
}

std::string File::_fmt_time(std::chrono::system_clock::time_point const& tp) const
{
	auto timestamp = std::chrono::system_clock::to_time_t(tp);
	auto localts = std::localtime(&timestamp);
	char cstr[128];
	std::strftime(cstr, sizeof(cstr), "%c", localts);

	return std::string(cstr);
}

} // namespace storage

} // namespace capture
