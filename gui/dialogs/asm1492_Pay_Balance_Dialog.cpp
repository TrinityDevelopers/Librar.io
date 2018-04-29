#include "asm1492_Pay_Balance_Dialog.h"

#include "../elements/asm1492_Input_Frame.h"
#include "../../asm1492_Library.h"
#include "../../asm1492_Librarian.h"
#include "../../asm1492_Customer.h"

Pay_Balance_Dialog::Pay_Balance_Dialog(Gtk::Window& parent) 
	: Gtk::Dialog("Pay Balance", parent), customer(*this) {
	
	set_resizable(false);
	set_size_request(350);

	customer.get_combo()->signal_changed().connect(sigc::mem_fun(*this, &Pay_Balance_Dialog::update_balance));
	Input_Frame* frame = Gtk::manage(new Input_Frame("Customer", &customer));
	get_content_area()->pack_start(*frame);

	update_balance();

	add_button("_Cancel", 0);
	add_action_widget(pay_balance_button, 1);

	get_action_area()->set_layout(Gtk::BUTTONBOX_EXPAND);

	show_all_children();
}

void Pay_Balance_Dialog::pay_balance() {
	if(customer.get_selected() != NULL)
		customer.get_selected()->pay_balance();
}

void Pay_Balance_Dialog::update_balance() {
	if(customer.get_selected() != NULL && customer.get_selected()->get_balance() != 0.0) {
		pay_balance_button.set_label("Pay Balance - " + customer.get_selected()->get_balance_string());
		pay_balance_button.set_sensitive(true);
	}
	else {
		pay_balance_button.set_label("Pay Balance");
		pay_balance_button.set_sensitive(false);
	}
}