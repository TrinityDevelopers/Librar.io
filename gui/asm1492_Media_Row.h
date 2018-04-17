#pragma once

#include <gtkmm.h>

#include "../media/asm1492_Media.h"

class Media_Row : public Gtk::ListBoxRow {
public:
	Media_Row(Media* media_);
	Media* get_media() { return media; };
	
private:
	Glib::RefPtr<Gdk::Pixbuf> icon_from_format(Media::Format form);

	Gtk::Label title;
	Gtk::Label genre;
	Gtk::Label availability;
	Gtk::Label id_num;
	Gtk::Label format;
	Gtk::Image format_icon;
	Media* media;
};