#pragma once

#include <gtkmm.h>

class Bundle;
class User_Window;

class Bundle_View : public Gtk::Box {
public:
	Bundle_View(User_Window& parent, Bundle* bundle_);
private:
	Bundle* bundle;
	Gtk::Button close;
};