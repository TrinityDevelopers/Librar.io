#pragma once

#include <gtkmm.h>

#include "../asm1492_Bundle.h"

class Bundle_Row : public Gtk::ListBoxRow {
public:
	Bundle_Row(Bundle* bundle);
private:
	Gtk::Label name;
	Gtk::Label medias;
	Gtk::Label availability;
	Gtk::Label format;
	Gtk::Image format_icon;
};