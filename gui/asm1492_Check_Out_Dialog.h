#pragma once

#include "asm1492_User_Select.h"
#include "asm1492_Browse_Window.h"
#include "asm1492_Date_Selection.h"

class Transaction;

class Check_Out_Dialog : public Gtk::Dialog {
public:
	Check_Out_Dialog(Gtk::Window& parent);
	virtual ~Check_Out_Dialog() {};
	Transaction* create_transaction();

private:
	Customer_Select customer;
	Librarian_Select librarian;
	Browse_Window items;
	Date_Selection date;
};