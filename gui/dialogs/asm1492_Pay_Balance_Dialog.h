#pragma once

#include "../elements/asm1492_User_Select.h"

class Pay_Balance_Dialog : public Gtk::Dialog {
public:
	Pay_Balance_Dialog(Gtk::Window& parent);
	virtual ~Pay_Balance_Dialog() {};
	void pay_balance();

private:
	void update_balance();

	Customer_Select customer;
	Gtk::Button pay_balance_button;
};