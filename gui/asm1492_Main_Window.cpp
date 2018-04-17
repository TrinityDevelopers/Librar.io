#include "asm1492_Main_Window.h"

#include "asm1492_Add_Media_Dialog.h"
#include "asm1492_Add_Bundle_Dialog.h"
#include "asm1492_Browse_Catalog_Dialog.h"

Main_Window::Main_Window()
	: add_media_button("Add Media"), add_bundle_button("Add Bundle"), browse_catalog_button("Browse Catalog") {
	
	add(button_box);

	button_box.set_layout(Gtk::BUTTONBOX_CENTER);
	button_box.set_spacing(20);

	button_box.pack_start(add_media_button);
	add_media_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::add_media_button_clicked));

	button_box.pack_start(add_bundle_button);
	add_bundle_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::add_bundle_button_clicked));

	button_box.pack_start(browse_catalog_button);
	browse_catalog_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::browse_catalog_button_clicked));

	show_all_children();
}

void Main_Window::add_media_button_clicked() {
	Add_Media_Dialog dialog(*this);
	if(dialog.run())
		dialog.create_media();
}

void Main_Window::add_bundle_button_clicked() {
	Add_Bundle_Dialog dialog(*this);
	if(dialog.run())
		dialog.create_bundle();
}

void Main_Window::browse_catalog_button_clicked() {
	Browse_Catalog_Dialog dialog(*this);
	dialog.run();
}