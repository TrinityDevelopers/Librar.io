#pragma once

#include "asm1492_User_Select.h"
#include "asm1492_Browse_Window.h"
#include "asm1492_Date_Selection.h"

class Check_In_Dialog : public Gtk::Dialog {
public:
	Check_In_Dialog(Gtk::Window& parent);
	virtual ~Check_In_Dialog() {};
	void check_in();

private:
	void update_items();

	Customer_Select customer;
	Librarian_Select librarian;
	Browse_Window items;
	Date_Selection date;
};