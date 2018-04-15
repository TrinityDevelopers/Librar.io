#include "asm1492_Main_Window.h"

#include "asm1492_Add_Media_Dialog.h"

Main_Window::Main_Window()
	: add_media_button("Add Media"), add_bundle_button("Add Bundle"), print_catalog_button("Print Catalog") {
	
	add(button_box);

	button_box.set_layout(Gtk::BUTTONBOX_CENTER);
	button_box.set_spacing(20);

	button_box.pack_start(add_media_button);
	add_media_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::add_media_button_clicked));

	button_box.pack_start(add_bundle_button);
	add_bundle_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::add_bundle_button_clicked));

	button_box.pack_start(print_catalog_button);
	print_catalog_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::print_catalog_button_clicked));

	show_all_children();
}

void Main_Window::add_media_button_clicked() {
	Add_Media_Dialog dialog(*this);
	dialog.run();
}

void Main_Window::add_bundle_button_clicked() {
	Gtk::MessageDialog dialog(*this, "Add Bundle Dialog");
	dialog.run();
}

void Main_Window::print_catalog_button_clicked() {
	Gtk::MessageDialog dialog(*this, "Print Catalog Dialog");
	dialog.run();
}