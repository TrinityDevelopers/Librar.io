#include "asm1492_User_Window.h"

#include "dialogs/asm1492_Add_Media_Dialog.h"
#include "dialogs/asm1492_Add_Bundle_Dialog.h"
#include "dialogs/asm1492_Check_Out_Dialog.h"
#include "dialogs/asm1492_Check_In_Dialog.h"
#include "dialogs/asm1492_Transaction_Dialog.h"
#include "dialogs/asm1492_Pay_Balance_Dialog.h"
#include "asm1492_Main_Window.h"
#include "elements/asm1492_Media_Row.h"
#include "elements/asm1492_Bundle_Row.h"
#include "elements/asm1492_Media_View.h"
#include "elements/asm1492_Bundle_View.h"
#include "../asm1492_Library.h"

User_Window::User_Window(Main_Window& parent_, User* user_)
	: Gtk::Box(Gtk::ORIENTATION_VERTICAL), parent(parent_), user(user_), filter_sort_box(Gtk::ORIENTATION_VERTICAL),
	  catalog_box(Gtk::ORIENTATION_VERTICAL), dialog_status(0) {
	
	parent.add_action("logout", sigc::mem_fun(parent, &Main_Window::logout));

	Gtk::Paned* panes = Gtk::manage(new Gtk::Paned());
	pack_start(*panes);

	Gtk::Frame* frame = Gtk::manage(new Gtk::Frame());
	frame->set_border_width(2);
	frame->add(filter_sort_box);
	panes->pack1(*frame, Gtk::FILL);

	frame = Gtk::manage(new Gtk::Frame());
	frame->set_border_width(2);
	catalog_box.set_border_width(5);
	button_box.set_layout(Gtk::BUTTONBOX_START);
	button_box.set_spacing(20);
	catalog_box.pack_start(button_box);
	Gtk::Box* action_box = Gtk::manage(new Gtk::Box());
	action_box->pack_start(items);
	action_box->pack_start(dialog, Gtk::PACK_SHRINK);
	catalog_box.pack_start(*action_box);
	frame->add(catalog_box);
	panes->pack2(*frame);

	frame = Gtk::manage(new Gtk::Frame());
	frame->set_border_width(5);
	Gtk::Expander* filter = Gtk::manage(new Gtk::Expander("<markup><b>_Narrow your search</b></markup>", true));
	filter->set_border_width(5);
	filter->set_size_request(220);
	filter->set_use_markup();
	filter->set_label_fill();
	filter->set_expanded();
	Gtk::Box* filter_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	filter->add(*filter_box);
	frame->add(*filter);
	filter_sort_box.pack_start(*frame, Gtk::PACK_SHRINK);

	frame = Gtk::manage(new Gtk::Frame());
	filter = Gtk::manage(new Gtk::Expander("_Format", true));
	filter->set_border_width(5);
	filter->set_label_fill();
	setup_format_filters(filter);
	frame->add(*filter);
	filter_box->pack_start(*frame, Gtk::PACK_SHRINK);

	frame = Gtk::manage(new Gtk::Frame());
	filter = Gtk::manage(new Gtk::Expander("_Availability", true));
	filter->set_border_width(5);
	filter->set_label_fill();
	setup_availability_filters(filter);
	frame->add(*filter);
	filter_box->pack_start(*frame, Gtk::PACK_SHRINK);

	dialog.set_transition_type(Gtk::REVEALER_TRANSITION_TYPE_SLIDE_LEFT);
	dialog.set_transition_duration(500);
	items.get_listbox()->set_activate_on_single_click(false);

	items.get_listbox()->signal_row_activated().connect(sigc::mem_fun(*this, &User_Window::item_activated));
	items.get_listbox()->signal_row_selected().connect(sigc::mem_fun(*this, &User_Window::item_selected));

	refresh_items();

	show_all();
}

void User_Window::set_inactive() {
	parent.remove_action("logout");
}

void User_Window::refresh_items() {
	close_dialog();
	items.clear();

	bool format_filter_enable = false;
	bool availability_filter_enable = false;

	for(Gtk::CheckButton* filter : format_filters)
		if(filter->get_active())
			format_filter_enable = true;

	for(Gtk::CheckButton* filter : availability_filters)
		if(filter->get_active())
			availability_filter_enable = true;

	for(Media* media : Library::get_instance()->get_all_medias())
		if(!format_filter_enable || format_filters[(int)media->get_format()]->get_active())
			if(!availability_filter_enable || availability_filters[(int)media->is_checked_out()]->get_active())
				items.add_row(new Media_Row(media));
	
	for(Bundle* bundle : Library::get_instance()->get_all_bundles())
		if(!format_filter_enable || format_filters[6]->get_active())
			if(!availability_filter_enable || availability_filters[(int)bundle->is_checked_out()]->get_active())
				items.add_row(new Bundle_Row(bundle));
}

void User_Window::setup_format_filters(Gtk::Expander* format_expander) {
	Gtk::Box* filter_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	format_expander->add(*filter_box);
	for(int format = 0; format < 6; format++)
		format_filters.push_back(Gtk::manage(new Gtk::CheckButton(Media::format_to_string((Media::Format)format))));
	format_filters.push_back(Gtk::manage(new Gtk::CheckButton("Bundle")));
	for(Gtk::CheckButton* filter : format_filters) {
		filter->signal_toggled().connect(sigc::mem_fun(*this, &User_Window::refresh_items));
		filter_box->pack_start(*filter);
	}
}

void User_Window::setup_availability_filters(Gtk::Expander* availability_expander) {
	Gtk::Box* filter_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	availability_expander->add(*filter_box);
	availability_filters.push_back(Gtk::manage(new Gtk::CheckButton("Checked In")));
	availability_filters.push_back(Gtk::manage(new Gtk::CheckButton("Checked Out")));
	for(Gtk::CheckButton* filter : availability_filters) {
		filter->signal_toggled().connect(sigc::mem_fun(*this, &User_Window::refresh_items));
		filter_box->pack_start(*filter);
	}
}

void User_Window::item_activated(Gtk::ListBoxRow* row) {
	dialog.remove();
	if(((Catalog_Row*) row)->get_type() == Catalog_Row::Type::MEDIA) {
		dialog.add(*Gtk::manage(new Media_View(*this, ((Media_Row*) row)->get_media())));
	}
	else if(((Catalog_Row*) row)->get_type() == Catalog_Row::Type::BUNDLE) {
		dialog.add(*Gtk::manage(new Bundle_View(*this, ((Bundle_Row*) row)->get_bundle())));
	}
	dialog.set_reveal_child();
	dialog_status = 2;
}

void User_Window::item_selected(Gtk::ListBoxRow* row) {
	if(dialog_status == 1)
		close_dialog();
	dialog_status--;
}

Administrator_Window::Administrator_Window(Main_Window& parent_, User* admin) : User_Window(parent_, admin), add_media_button("Add Media"), add_bundle_button("Add Bundle") {
	parent.set_title("Librar.io - Administrator");
	parent.add_action("add_media", sigc::mem_fun(*this, &Administrator_Window::add_media_button_clicked));
	parent.add_action("add_bundle", sigc::mem_fun(*this, &Administrator_Window::add_bundle_button_clicked));

	button_box.pack_start(add_media_button);
	add_media_button.signal_clicked().connect(sigc::mem_fun(*this, &Administrator_Window::add_media_button_clicked));

	button_box.pack_start(add_bundle_button);
	add_bundle_button.signal_clicked().connect(sigc::mem_fun(*this, &Administrator_Window::add_bundle_button_clicked));

	button_box.show_all();
}

void Administrator_Window::set_inactive() {
	User_Window::set_inactive();
	parent.remove_action("add_media");
	parent.remove_action("add_bundle");
}

void Administrator_Window::add_media_button_clicked() {
	Add_Media_Dialog dialog(parent);
	if(dialog.run()) {
		dialog.create_media();
		refresh_items();
	}
}

void Administrator_Window::add_bundle_button_clicked() {
	Add_Bundle_Dialog dialog(parent);
	if(dialog.run()) {
		dialog.create_bundle();
		refresh_items();
	}
}

Librarian_Window::Librarian_Window(Main_Window& parent_, User* librarian) : User_Window(parent_, librarian), check_out_button("Check Out"), check_in_button("Check In") {
	parent.set_title("Librar.io - Librarian");
	parent.add_action("check_out", sigc::mem_fun(*this, &Librarian_Window::check_out_button_clicked));
	parent.add_action("check_in", sigc::mem_fun(*this, &Librarian_Window::check_in_button_clicked));

	button_box.pack_start(check_out_button);
	check_out_button.signal_clicked().connect(sigc::mem_fun(*this, &Librarian_Window::check_out_button_clicked));

	button_box.pack_start(check_in_button);
	check_in_button.signal_clicked().connect(sigc::mem_fun(*this, &Librarian_Window::check_in_button_clicked));

	button_box.show_all();
}

void Librarian_Window::set_inactive() {
	User_Window::set_inactive();
	parent.remove_action("check_in");
	parent.remove_action("check_out");
}

void Librarian_Window::check_out_button_clicked() {
	Check_Out_Dialog dialog(parent);
	if(dialog.run()) {
		Transaction_Dialog trans_dialog(parent, dialog.create_transaction());
		trans_dialog.run();
		refresh_items();
	}
}

void Librarian_Window::check_in_button_clicked() {
	Check_In_Dialog dialog(parent);
	if(dialog.run()) {
		dialog.check_in();
		refresh_items();
	}
}

Customer_Window::Customer_Window(Main_Window& parent_, User* customer) : User_Window(parent_, customer), pay_balance_button("Pay Balance") {
	parent.set_title("Librar.io - Customer");
	parent.add_action("pay_balance", sigc::mem_fun(*this, &Customer_Window::pay_balance_button_clicked));

	button_box.pack_start(pay_balance_button);
	pay_balance_button.signal_clicked().connect(sigc::mem_fun(*this, &Customer_Window::pay_balance_button_clicked));

	button_box.show_all();
}

void Customer_Window::set_inactive() {
	User_Window::set_inactive();
	parent.remove_action("pay_balance");
}

void Customer_Window::pay_balance_button_clicked() {
	Pay_Balance_Dialog dialog(parent);
	if(dialog.run())
		dialog.pay_balance();
}