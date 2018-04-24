#pragma once

#include <gtkmm.h>
#include "asm1492_Browse_Window.h"

class Transaction;

class Transaction_Dialog : public Gtk::Dialog {
public:
	Transaction_Dialog(Gtk::Window& parent, Transaction* trans);
private:
	Gtk::Label trans_num;
	Gtk::Label trans_date;
	Gtk::Label librarian;
	Gtk::Label customer;
	Browse_Window items;
};