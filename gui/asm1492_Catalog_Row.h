#pragma once

#include <gtkmm.h>
#include "../asm1492_Date.h"

class Catalog_Row : public Gtk::ListBoxRow {
public:
	enum class Type : unsigned char {
		MEDIA,
		BUNDLE
	};

	Catalog_Row(Type type_);
	Type get_type() { return type; };
	
protected:
	Type type;
	Gtk::Box left_box{Gtk::ORIENTATION_VERTICAL}, right_box{Gtk::ORIENTATION_VERTICAL};
	Gtk::Label title;
	Gtk::Label medias;
	Gtk::Label genre;
	Gtk::Label availability;
	Gtk::Label date;
	Gtk::Label id_num;
	Gtk::Label format;
	Gtk::Image format_icon;
};