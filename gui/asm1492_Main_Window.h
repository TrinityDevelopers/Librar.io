#pragma once

#include <gtkmm.h>
#include "../asm1492_User.h"

class Login_Window;
class User_Window;

class Main_Window : public Gtk::ApplicationWindow {
public:
	explicit Main_Window();
	void login(User* user);
	void logout();
	bool on_delete_event(GdkEventAny* any_event) override;

protected:
	void exit_library();
	void new_library();
	void open_library();
	bool prompt_save();
	bool save();
	bool save_as();
	void save_menu() { save(); };
	void save_as_menu() { save_as(); };

	void about();

	/*void add_media_button_clicked();
	void add_bundle_button_clicked();
	void browse_catalog_button_clicked();
	void create_librarian_button_clicked();
	void create_customer_button_clicked();
	void check_out_button_clicked();
	void check_in_button_clicked();
	void pay_balance_button_clicked();

	Gtk::Grid button_box;
	Gtk::Button add_media_button;
	Gtk::Button add_bundle_button;
	Gtk::Button browse_catalog_button;
	Gtk::Button create_librarian_button;
	Gtk::Button create_customer_button;
	Gtk::Button check_out_button;
	Gtk::Button check_in_button;
	Gtk::Button pay_balance_button;*/
	Login_Window* login_window;
	User_Window* user_window;
};