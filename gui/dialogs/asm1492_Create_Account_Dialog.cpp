#include "asm1492_Create_Account_Dialog.h"

#include "../../asm1492_Library.h"
#include "../../asm1492_User.h"
#include "../../asm1492_Customer.h"
#include "../../asm1492_Librarian.h"
#include "../../asm1492_picosha2.h"

Create_Account_Dialog::Create_Account_Dialog(Gtk::Window& parent)
	: Gtk::Dialog("Create Account", parent) {
	
	set_resizable(false);
	set_size_request(250);

	for(int type = 0; type < 3; type++)
		user_type.append(User::string_from_type((User::Type)type));
	user_type.set_active(0);
	Input_Frame* frame = Gtk::manage(new Input_Frame("Account Type", &user_type));
	get_content_area()->pack_start(*frame);
	user_type.signal_changed().connect(sigc::mem_fun(*this, &Create_Account_Dialog::user_type_changed));
	frame->show_all();

	name.set_placeholder_text("Name");
	name.set_activates_default();
	frame = Gtk::manage(new Input_Frame("Full Name", &name));
	get_content_area()->pack_start(*frame);
	frame->show_all();

	phone.set_placeholder_text("XXXXXXXXXX");
	phone.set_activates_default();
	phone_frame = Gtk::manage(new Input_Frame("Phone Number", &phone));
	get_content_area()->pack_start(*phone_frame);

	email.set_placeholder_text("Email");
	email.set_activates_default();
	email_frame = Gtk::manage(new Input_Frame("Email Address", &email));
	get_content_area()->pack_start(*email_frame);

	password.set_placeholder_text("Password");
	password.set_activates_default();
	password.set_input_purpose(Gtk::INPUT_PURPOSE_PASSWORD);
	password.set_visibility(false);
	password.set_icon_from_icon_name("dialog-password", Gtk::ENTRY_ICON_SECONDARY);
	password.signal_icon_press().connect(sigc::mem_fun(*this, &Create_Account_Dialog::password_show));
	password.signal_icon_release().connect(sigc::mem_fun(*this, &Create_Account_Dialog::password_hide));
	frame = Gtk::manage(new Input_Frame("Password", &password));
	get_content_area()->pack_start(*frame);
	frame->show_all();

	user_type_changed();
	
	add_button("_Cancel", 0);
	add_action_widget(create_account_button, 1);
	create_account_button.set_can_default();
	create_account_button.show();
	set_default_response(1);

	get_action_area()->set_layout(Gtk::BUTTONBOX_EXPAND);
}

User* Create_Account_Dialog::create_account() {
	switch((User::Type) user_type.get_active_row_number()) {
		case User::Type::Customer:
			return Library::get_instance()->create_new_customer(name.get_text(), phone.get_long(), email.get_text(), picosha2::hash256_hex_string(password.get_text()));
		case User::Type::Librarian:
			return Library::get_instance()->create_new_librarian(name.get_text(), picosha2::hash256_hex_string(password.get_text()));
		case User::Type::Administrator:
			return Library::get_instance()->create_administrator(name.get_text(), picosha2::hash256_hex_string(password.get_text()));
	}
	return NULL;
}

void Create_Account_Dialog::user_type_changed() {
	phone_frame->hide();
	email_frame->hide();
	User::Type type = (User::Type) user_type.get_active_row_number();
	create_account_button.set_label("Create Account # " + std::to_string(Library::get_instance()->get_current_librarian_id()));
	if(type == User::Type::Customer) {
		phone_frame->clear_and_show();
		email_frame->clear_and_show();
		create_account_button.set_label("Create Account # " + std::to_string(Library::get_instance()->get_current_customer_id()));
	}
}