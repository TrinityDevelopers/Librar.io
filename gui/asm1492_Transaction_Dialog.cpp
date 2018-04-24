#include "asm1492_Transaction_Dialog.h"

#include "asm1492_Media_Row.h"
#include "asm1492_Bundle_Row.h"
#include "asm1492_Input_Frame.h"
#include "../asm1492_Transaction.h"
#include "../asm1492_Date.h"
#include "../asm1492_Librarian.h"
#include "../asm1492_Customer.h"

Transaction_Dialog::Transaction_Dialog(Gtk::Window& parent, Transaction* trans)
	: Gtk::Dialog("Check Out Receipt", parent) {
	
	set_resizable(false);

	trans_num.set_markup("<markup>Transaction Number: <b> " + to_string(trans->get_transaction_number()) + "</b></markup>");
	trans_date.set_markup("<markup>Check Out Date: <b> " + trans->get_check_out_date().to_string() + "</b></markup>");
	librarian.set_markup("<markup>Librarian: <b> " + trans->get_librarian()->to_compact_string() + "</b></markup>");
	customer.set_markup( "<markup>Customer: <b> " + trans->get_customer()->to_compact_string() + "</b></markup>");
	trans_num.set_halign(Gtk::ALIGN_START);
	trans_date.set_halign(Gtk::ALIGN_START);
	librarian.set_halign(Gtk::ALIGN_START);
	customer.set_halign(Gtk::ALIGN_START);

	get_content_area()->pack_start(trans_num);
	get_content_area()->pack_start(trans_date);
	get_content_area()->pack_start(librarian);
	get_content_area()->pack_start(customer);

	Gtk::Box* box = Gtk::manage(new Gtk::Box());
	get_content_area()->pack_start(*box);
	Gtk::Box* box_left = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	box->pack_start(*box_left);
	Gtk::Frame* media_frame = Gtk::manage(new Gtk::Frame("Checked Out Items"));
	box_left->pack_start(*media_frame);
	Gtk::Box* media_box = Gtk::manage(new Gtk::Box());
	media_box->set_border_width(10);
	media_box->pack_start(items);
	media_frame->add(*media_box);

	for(Transaction_Item item : trans->get_items()) {
		if(item.get_type() == Transaction_Item::Type::MEDIA)
			items.add_row(new Media_Row(item.get_media(), item.get_due_date()));
		else if(item.get_type() == Transaction_Item::Type::BUNDLE)
			items.add_row(new Bundle_Row(item.get_bundle(), item.get_due_date()));
	}

	add_button("_OK", 0);
	set_default_response(0);

	show_all_children();
}