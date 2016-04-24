#include "time.h"

#if defined(__linux__) || defined(__linux) || defined(linux)
#include <sys/sysinfo.h>
#endif

namespace capture
{

namespace util
{

unsigned int uptime()
{
#if defined(__linux__) || defined(__linux) || defined(linux)
	struct sysinfo info;
	if (sysinfo(&info) != 0)
	{
		// TODO error handling
		return 0;
	}

	return info.uptime;
#endif
}

} // namespace util

} // namespace capture
