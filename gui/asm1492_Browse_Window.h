#pragma once

#include <gtkmm.h>
#include <vector>

#include "../media/asm1492_Media.h"

using namespace std;

class Browse_Window : public Gtk::ScrolledWindow {
public:
	Browse_Window(bool select = false);
	void add_row(Gtk::ListBoxRow* unmanaged_row);
	vector<Media*> get_selected_media();

private:
	bool selectable;
	Gtk::Box vbox;
	Gtk::ListBox medias;
};