#include "asm1492_Check_In_Dialog.h"

#include "../elements/asm1492_Media_Row.h"
#include "../elements/asm1492_Bundle_Row.h"
#include "../elements/asm1492_Input_Frame.h"
#include "../../asm1492_Library.h"
#include "../../asm1492_Librarian.h"
#include "../../asm1492_Customer.h"

Check_In_Dialog::Check_In_Dialog(Gtk::Window& parent) 
	: Gtk::Dialog("Check In", parent), customer(*this), librarian(*this), items(true) {
	
	set_resizable(false);

	customer.get_combo()->signal_changed().connect(sigc::mem_fun(*this, &Check_In_Dialog::update_items));
	Input_Frame* frame = Gtk::manage(new Input_Frame("Customer", &customer));
	get_content_area()->pack_start(*frame);

	frame = Gtk::manage(new Input_Frame("Librarian", &librarian));
	get_content_area()->pack_start(*frame);

	Gtk::Box* box = Gtk::manage(new Gtk::Box());
	get_content_area()->pack_start(*box);
	Gtk::Box* box_left = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	box->pack_start(*box_left);
	Gtk::Frame* media_frame = Gtk::manage(new Gtk::Frame("Select Items to Check In"));
	box_left->pack_start(*media_frame);
	Gtk::Box* media_box = Gtk::manage(new Gtk::Box());
	media_box->set_border_width(10);
	media_box->pack_start(items);
	media_frame->add(*media_box);

	update_items();

	frame = Gtk::manage(new Input_Frame("Check In Date", &date));
	get_content_area()->pack_start(*frame);

	add_button("_Cancel", 0);
	add_button("_OK", 1);

	get_action_area()->set_layout(Gtk::BUTTONBOX_EXPAND);

	show_all_children();
}

void Check_In_Dialog::check_in() {
	if(librarian.get_selected() != NULL && customer.get_selected() != NULL)
		librarian.get_selected()->check_in(customer.get_selected(), items.get_selected_media(), items.get_selected_bundles(), date.get_date());
}

void Check_In_Dialog::update_items() {
	if(customer.get_selected() != NULL) {
		items.clear();
		for(Transaction_Item item : customer.get_selected()->get_checked_out_items()) {
			if(item.get_type() == Transaction_Item::Type::MEDIA)
				items.add_row(new Media_Row(item.get_media(), item.get_due_date()));
			else if(item.get_type() == Transaction_Item::Type::BUNDLE)
				items.add_row(new Bundle_Row(item.get_bundle(), item.get_due_date()));
		}
	}
}