#pragma once

#include <gtkmm.h>

#include "asm1492_Browse_Window.h"

class Media;
class Bundle;

class Browse_Catalog_Dialog : public Gtk::Dialog {
public:
	Browse_Catalog_Dialog(Gtk::Window& parent);
	virtual ~Browse_Catalog_Dialog() {};

	void add_media(Media* media);
	void add_bundle(Bundle* bundle);
private:
	Gtk::Box box;
	Gtk::Box box_left;
	Browse_Window medias;
};