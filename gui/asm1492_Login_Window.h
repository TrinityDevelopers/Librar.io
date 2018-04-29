#pragma once

#include "elements/asm1492_Input_Frame.h"

class Main_Window;

class Login_Window : public Gtk::Box {
public:
	Login_Window(Main_Window& parent);
	void set_inactive();

private:
	void do_login();
	void create_account();
	void password_show(Gtk::EntryIconPosition icon_position, const GdkEventButton* event) { password.set_visibility(true); };
	void password_hide(Gtk::EntryIconPosition icon_position, const GdkEventButton* event) { password.set_visibility(false); };

	Main_Window& parent;
	Gtk::Image logo;
	Gtk::Label invalid_label;
	Gtk::Button create_account_button;
	Gtk::Button login_button;
	Clearable_Entry id;
	Clearable_Entry password;
};