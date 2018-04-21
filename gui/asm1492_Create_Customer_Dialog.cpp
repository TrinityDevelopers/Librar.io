#include "asm1492_Create_Customer_Dialog.h"

#include "asm1492_Media_Row.h"
#include "../asm1492_Library.h"

Create_Customer_Dialog::Create_Customer_Dialog(Gtk::Window& parent)
	: Gtk::Dialog("Add Customer", parent) {
	
	set_resizable(false);

	name.set_placeholder_text("Name");
	name.set_activates_default();
	Input_Frame* frame = Gtk::manage(new Input_Frame("Customer Name", &name));
	get_content_area()->pack_start(*frame);

	phone.set_placeholder_text("XXXXXXXXXX");
	phone.set_activates_default();
	frame = Gtk::manage(new Input_Frame("Phone Number", &phone));
	get_content_area()->pack_start(*frame);

	email.set_placeholder_text("Email");
	email.set_activates_default();
	frame = Gtk::manage(new Input_Frame("Email Address", &email));
	get_content_area()->pack_start(*frame);

	add_button("_Cancel", 0);
	add_button("_OK", 1);
	set_default_response(1);

	get_action_area()->set_layout(Gtk::BUTTONBOX_EXPAND);

	show_all_children();
}

Customer* Create_Customer_Dialog::create_customer() {
	return Library::get_instance()->create_new_customer(name.get_text(), phone.get_long(), email.get_text());
}