#pragma one

#include "window.h"

typedef struct _XDisplay Display;

typedef unsigned long int XID;
typedef XID Window;

namespace capture
{

namespace x
{

class XAdapter
{
public:
	XAdapter();
	~XAdapter();

	void connect();
	bool is_connected() const;

	WindowProperties focus_window_properties() const;

private:
	Window _true_window(Window& window) const;
	std::string _request_txt_property(
			  Window& window
			, std::string const& prop_name) const;
	unsigned int _request_int_property(
			  Window& window
			, std::string const& prop_name) const;

private:
	Display* _display;
};

} // namespace x

} // namespace capture
