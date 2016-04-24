#include "xadapter.h"

#include "../util/time.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace capture
{

namespace x
{

XAdapter::XAdapter()
: _display(nullptr)
{
}

XAdapter::~XAdapter()
{
	if (_display)
		XCloseDisplay(_display);
}

void XAdapter::connect()
{
	if (not _display)
		_display = XOpenDisplay(0);
}

bool XAdapter::is_connected() const
{
	return _display;
}

WindowProperties XAdapter::focus_window_properties() const
{
	WindowProperties window;

	::Window focus_window;
	int revert;

	XGetInputFocus(_display, &focus_window, &revert);
	focus_window = _true_window(focus_window);

	window.name = _request_txt_property(focus_window, "WM_NAME");
	window.xclass = _request_txt_property(focus_window, "WM_CLASS");
	window.command = _request_txt_property(focus_window, "WM_COMMAND");

	unsigned int x_nut =
		_request_int_property(focus_window, "_NET_WM_USER_TIME") / 1000;
	window.idle = util::uptime() - x_nut;

	return window;
}

Window XAdapter::_true_window(Window& window) const
{
     Window parent;
     Window root;

     Window *children;
     unsigned int num_children;

     while (true) {
         if (0 == XQueryTree(_display, window, &root,
                   &parent, &children, &num_children))
		 {
             abort(); // TODO throw
         }

         if (children)
             XFree(children);

         if (window == root or parent == root)
             return window;
         else
             window = parent;
     }
}

std::string XAdapter::_request_txt_property(
		  Window& window
		, std::string const& prop_name) const
{
	Atom atom_wm_name = XInternAtom(_display, prop_name.c_str(), false);

	XTextProperty property;
	XGetTextProperty(_display, window, &property, atom_wm_name);

	if (not property.value)
		return "";

	return std::string((char*)property.value);
}

unsigned int XAdapter::_request_int_property(
		  Window& window
		, std::string const& prop_name) const
{
	Atom atom_prop = XInternAtom(_display, prop_name.c_str(), false);
	Atom atom_type_req = XInternAtom(_display, "CARDINAL", false);
	Atom atom_type_ret;
	int format_ret;
	unsigned long nitems_ret;
	unsigned long bytes_after_ret;
	unsigned char* data = nullptr;

	int status = XGetWindowProperty(
			  _display
			, window
			, atom_prop
			, 0
			, 4
			, false
			, atom_type_req
			, &atom_type_ret
			, &format_ret
			, &nitems_ret
			, &bytes_after_ret
			, &data);

	if (	   status != 0
			or atom_type_req != atom_type_ret
			or data == nullptr)
	{
		// TODO error handling
		return 0;
	}

	return *reinterpret_cast<unsigned int*>(data);
}

} // namespace x

} // namespace capture
