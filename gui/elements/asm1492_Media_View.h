#pragma once

#include <gtkmm.h>

class Media;
class User_Window;

class Media_View : public Gtk::Box {
public:
	Media_View(User_Window& parent, Media* media_);
private:
	Media* media;
	Gtk::Button close;
};