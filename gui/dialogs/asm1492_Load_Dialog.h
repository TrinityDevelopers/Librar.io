#pragma once

#include <gtkmm.h>

class Load_Dialog : public Gtk::FileChooserDialog {
public:
	Load_Dialog(Gtk::Window& parent);

private:
	void update_open_button();

	Gtk::Button* open_button;
};