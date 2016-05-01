#pragma once

#include "log.h"

#include <chrono>
#include <string>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace boost::filesystem;
using namespace boost::gregorian;

namespace capture
{

namespace storage
{

class File : public Log
{
public:
	File(path const& cap_dir, std::string const& name);
	~File();

	void append(Entry const& entry);

private:
	bool _has_date_changed() const;
	void _check_and_create_cap_dir();
	void _change_file();
	path _cap_file_path() const;
	std::string _fmt(Entry const& entry) const;
	std::string _fmt_time(std::chrono::system_clock::time_point const& tp) const;

private:
	path         _cap_dir;
	std::string  _name;
	std::fstream _file;
	date         _date;
};

} // namespace storage

} // namespace capture