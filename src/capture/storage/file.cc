#include "file.h"

#include "entry.h"

#include <sstream>

namespace capture
{

namespace storage
{

File::File(path const& cap_dir, std::string const& name)
: _cap_dir(cap_dir)
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
	{
		_check_and_create_cap_dir();
		_change_file();
	}

	_file << _fmt(entry) << std::endl;
}

bool File::_has_date_changed() const
{
	return _date != day_clock::local_day();
}

void File::_check_and_create_cap_dir()
{
	if (is_directory(_cap_dir))
		return;

	create_directories(_cap_dir);
}

void File::_change_file()
{
	_date = day_clock::local_day();
	_file.open(_cap_file_path().native(), std::ios::out | std::ios::app);
}

path File::_cap_file_path() const
{
	std::string const cap_file_name =
		to_iso_extended_string(_date) + "_" + _name;

	path cap_file_path = _cap_dir;
	cap_file_path /= cap_file_name;

	return cap_file_path;
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
