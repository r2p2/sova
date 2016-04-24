#pragma once

#include <string>

namespace capture
{

namespace x
{

struct WindowProperties
{
	std::string  name;
	std::string  xclass;
	std::string  command;
	unsigned int idle;
};

} // nameespace x

} // namespace capture
