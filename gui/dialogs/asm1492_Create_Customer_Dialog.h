#pragma once

#include <gtkmm.h>

#include "../elements/asm1492_Input_Frame.h"

class Customer;

class Create_Customer_Dialog : public Gtk::Dialog {
public:
	Create_Customer_Dialog(Gtk::Window& parent);
	virtual ~Create_Customer_Dialog() {};
	Customer* create_customer();

private:
	Clearable_Entry name;
	Clearable_Entry phone;
	Clearable_Entry email;
};