#pragma once

#include <gtkmm.h>
#include <string>

using namespace std;

class Save_Dialog : public Gtk::FileChooserDialog {
public:
	Save_Dialog(Gtk::Window& parent);
	string get_current_path();

private:
	Gtk::Button* save_button;
};