#pragma once

#include <gtkmm.h>

class Main_Window : public Gtk::Window {
public:
	Main_Window();

protected:
	void add_media_button_clicked();
	void add_bundle_button_clicked();
	void print_catalog_button_clicked();

	Gtk::ButtonBox button_box;
	Gtk::Button add_media_button;
	Gtk::Button add_bundle_button;
	Gtk::Button print_catalog_button;
};