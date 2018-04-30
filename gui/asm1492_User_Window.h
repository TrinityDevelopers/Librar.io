#pragma once

#include <vector>

#include "elements/asm1492_Browse_Window.h"
#include "../asm1492_Librarian.h"
#include "../asm1492_Customer.h"

using namespace std;

class Main_Window;
class Media_View;
class Bundle_View;

class User_Window : public Gtk::Box {
public:
	User_Window(Main_Window& parent_, User* user_);
	virtual void set_inactive();
	void close_dialog() { dialog.set_reveal_child(false); };
	void set_dialog_status(int status) { dialog_status = status; };

protected:
	void refresh_items();
	void setup_format_filters(Gtk::Expander* format_expander);
	void setup_availability_filters(Gtk::Expander* availability_expander);
	void item_activated(Gtk::ListBoxRow* row);
	void item_selected(Gtk::ListBoxRow* row);

	Main_Window& parent;
	User* user;
	Browse_Window items;
	Gtk::Revealer dialog;
	int dialog_status;
	Gtk::Box filter_sort_box;
	vector<Gtk::CheckButton*> format_filters;
	vector<Gtk::CheckButton*> availability_filters;
	Gtk::Box catalog_box;
	Gtk::ButtonBox button_box;
};

class Administrator_Window : public User_Window {
public:
	Administrator_Window(Main_Window& parent_, User* admin);
	void set_inactive();

private:
	void add_media_button_clicked();
	void add_bundle_button_clicked();

	Gtk::Button add_media_button;
	Gtk::Button add_bundle_button;
};

class Librarian_Window : public User_Window {
public:
	Librarian_Window(Main_Window& parent_, User* librarian);
	void set_inactive();

private:
	void check_out_button_clicked();
	void check_in_button_clicked();
	
	Gtk::Button check_out_button;
	Gtk::Button check_in_button;
};

class Customer_Window : public User_Window {
public:
	Customer_Window(Main_Window& parent_, User* customer);
	void set_inactive();

private:
	void pay_balance_button_clicked();
	
	Gtk::Button pay_balance_button;
};