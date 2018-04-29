#pragma once

#include "../elements/asm1492_Input_Frame.h"

class User;

class Create_Account_Dialog : public Gtk::Dialog {
public:
	Create_Account_Dialog(Gtk::Window& parent);
	virtual ~Create_Account_Dialog() {};
	User* create_account();

private:
	void user_type_changed();
	void password_show(Gtk::EntryIconPosition icon_position, const GdkEventButton* event) { password.set_visibility(true); };
	void password_hide(Gtk::EntryIconPosition icon_position, const GdkEventButton* event) { password.set_visibility(false); };

	Gtk::ComboBoxText user_type;
	Gtk::Button create_account_button;
	Clearable_Entry name;
	Clearable_Entry phone;
	Input_Frame* phone_frame;
	Clearable_Entry email;
	Input_Frame* email_frame;
	Clearable_Entry password;
};