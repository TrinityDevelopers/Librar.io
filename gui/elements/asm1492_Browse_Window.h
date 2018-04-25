#pragma once

#include <gtkmm.h>
#include <vector>

#include "../../media/asm1492_Media.h"
#include "../../asm1492_Bundle.h"

using namespace std;

class Browse_Window : public Gtk::ScrolledWindow {
public:
	Browse_Window(bool select = false);
	void add_row(Gtk::ListBoxRow* unmanaged_row);
	void clear();
	vector<Media*> get_selected_media();
	vector<Bundle*> get_selected_bundles();

private:
	bool selectable;
	Gtk::Box vbox;
	Gtk::ListBox medias;
};