#pragma once

#include <gtkmm.h>
#include <vector>

using namespace std;

class Customer;
class Librarian;

class Customer_Select : public Gtk::Box {
public:
	Customer_Select(Gtk::Window& parent);
	Customer* get_selected();
	Gtk::ComboBoxText* get_combo() { return &combo_box; };

private:
	void new_customer_clicked();

	Gtk::Window& window;
	Gtk::Button new_customer;
	Gtk::ComboBoxText combo_box;
	vector<Customer*> customers;
};

class Librarian_Select : public Gtk::Box {
public:
	Librarian_Select(Gtk::Window& parent);
	Librarian* get_selected();
	Gtk::ComboBoxText* get_combo() { return &combo_box; };
	
private:
	void new_librarian_clicked();

	Gtk::Window& window;
	Gtk::Button new_librarian;
	Gtk::ComboBoxText combo_box;
	vector<Librarian*> librarians;
};