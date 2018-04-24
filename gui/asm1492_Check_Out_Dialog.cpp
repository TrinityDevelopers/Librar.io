#include "asm1492_Check_Out_Dialog.h"

#include "asm1492_Media_Row.h"
#include "asm1492_Bundle_Row.h"
#include "asm1492_Input_Frame.h"
#include "../asm1492_Library.h"
#include "../asm1492_Librarian.h"
#include "../asm1492_Customer.h"

Check_Out_Dialog::Check_Out_Dialog(Gtk::Window& parent) 
	: Gtk::Dialog("Check Out", parent), customer(*this), librarian(*this), items(true) {
	
	set_resizable(false);

	Input_Frame* frame = Gtk::manage(new Input_Frame("Customer", &customer));
	get_content_area()->pack_start(*frame);

	frame = Gtk::manage(new Input_Frame("Librarian", &librarian));
	get_content_area()->pack_start(*frame);

	Gtk::Box* box = Gtk::manage(new Gtk::Box());
	get_content_area()->pack_start(*box);
	Gtk::Box* box_left = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	box->pack_start(*box_left);
	Gtk::Frame* media_frame = Gtk::manage(new Gtk::Frame("Select Items to Check Out"));
	box_left->pack_start(*media_frame);
	Gtk::Box* media_box = Gtk::manage(new Gtk::Box());
	media_box->set_border_width(10);
	media_box->pack_start(items);
	media_frame->add(*media_box);

	for(Media* media : Library::get_instance()->get_all_medias())
		if(!media->is_checked_out())
			items.add_row(new Media_Row(media));
	
	for(Bundle* bundle : Library::get_instance()->get_all_bundles())
		if(!bundle->is_checked_out())
			items.add_row(new Bundle_Row(bundle));

	frame = Gtk::manage(new Input_Frame("Check Out Date", &date));
	get_content_area()->pack_start(*frame);

	add_button("_Cancel", 0);
	add_button("_OK", 1);

	get_action_area()->set_layout(Gtk::BUTTONBOX_EXPAND);

	show_all_children();
}

Transaction* Check_Out_Dialog::create_transaction() {
	if(librarian.get_selected() != NULL && customer.get_selected() != NULL)
		return librarian.get_selected()->check_out(customer.get_selected(), items.get_selected_media(), items.get_selected_bundles(), date.get_date());
	return NULL;
}