#include "asm1492_Main_Window.h"

#include "asm1492_Add_Media_Dialog.h"
#include "asm1492_Add_Bundle_Dialog.h"
#include "asm1492_Browse_Catalog_Dialog.h"
#include "asm1492_Create_Librarian_Dialog.h"
#include "asm1492_Create_Customer_Dialog.h"
#include "asm1492_Check_Out_Dialog.h"
#include "asm1492_Check_In_Dialog.h"
#include "asm1492_Transaction_Dialog.h"

Main_Window::Main_Window()
	: add_media_button("Add Media"), add_bundle_button("Add Bundle"), browse_catalog_button("Browse Catalog"), 
	  create_librarian_button("Add Librarian"), create_customer_button("Add Customer"), check_out_button("Check Out"),
	  check_in_button("Check In") {
	
	set_default_size(900, 200);
	set_icon_name("accessories-dictionary");

	add(button_box);

	button_box.set_layout(Gtk::BUTTONBOX_CENTER);
	button_box.set_spacing(20);

	button_box.pack_start(add_media_button);
	add_media_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::add_media_button_clicked));

	button_box.pack_start(add_bundle_button);
	add_bundle_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::add_bundle_button_clicked));

	button_box.pack_start(browse_catalog_button);
	browse_catalog_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::browse_catalog_button_clicked));

	button_box.pack_start(create_librarian_button);
	create_librarian_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::create_librarian_button_clicked));

	button_box.pack_start(create_customer_button);
	create_customer_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::create_customer_button_clicked));

	button_box.pack_start(check_out_button);
	check_out_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::check_out_button_clicked));

	button_box.pack_start(check_in_button);
	check_in_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::check_in_button_clicked));

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

void Main_Window::create_librarian_button_clicked() {
	Create_Librarian_Dialog dialog(*this);
	if(dialog.run())
		dialog.create_librarian();
}

void Main_Window::create_customer_button_clicked() {
	Create_Customer_Dialog dialog(*this);
	if(dialog.run())
		dialog.create_customer();
}

void Main_Window::check_out_button_clicked() {
	Check_Out_Dialog dialog(*this);
	if(dialog.run()) {
		Transaction_Dialog trans_dialog(*this, dialog.create_transaction());
		trans_dialog.run();
	}
}

void Main_Window::check_in_button_clicked() {
	Check_In_Dialog dialog(*this);
	if(dialog.run())
		dialog.check_in();
}