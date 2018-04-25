#include "asm1492_User_Select.h"

#include "../dialogs/asm1492_Create_Customer_Dialog.h"
#include "../dialogs/asm1492_Create_Librarian_Dialog.h"
#include "../../asm1492_Library.h"
#include "../../asm1492_Customer.h"
#include "../../asm1492_Librarian.h"


Customer_Select::Customer_Select(Gtk::Window& parent)
	: Gtk::Box(Gtk::ORIENTATION_VERTICAL), new_customer("New Customer"), window(parent) {
	
	pack_start(new_customer);
	new_customer.set_image_from_icon_name("list-add");
	new_customer.signal_clicked().connect(sigc::mem_fun(*this, &Customer_Select::new_customer_clicked));
	pack_start(combo_box);

	customers = Library::get_instance()->get_all_customers();
	for(Customer* customer : customers)
		combo_box.append(customer->to_compact_string());
	combo_box.set_active(0);

	show_all_children();
}

Customer* Customer_Select::get_selected() {
	if(customers.size() >= combo_box.get_active_row_number())
		return customers[combo_box.get_active_row_number()];
	return NULL;
}

void Customer_Select::new_customer_clicked() {
	Create_Customer_Dialog dialog(window);
	if(dialog.run()) {
		Customer* customer = dialog.create_customer();
		combo_box.append(customer->to_compact_string());
		customers.push_back(customer);
	}
}

Librarian_Select::Librarian_Select(Gtk::Window& parent)
	: Gtk::Box(Gtk::ORIENTATION_VERTICAL), new_librarian("New Librarian"), window(parent) {
	
	pack_start(new_librarian);
	new_librarian.set_image_from_icon_name("list-add");
	new_librarian.signal_clicked().connect(sigc::mem_fun(*this, &Librarian_Select::new_librarian_clicked));
	pack_start(combo_box);

	librarians = Library::get_instance()->get_all_librarians();
	for(Librarian* librarian : librarians)
		combo_box.append(librarian->to_compact_string());
	combo_box.set_active(0);
	
	show_all_children();
}

Librarian* Librarian_Select::get_selected() {
	if(librarians.size() >= combo_box.get_active_row_number())
		return librarians[combo_box.get_active_row_number()];
	return NULL;
}

void Librarian_Select::new_librarian_clicked() {
	Create_Librarian_Dialog dialog(window);
	if(dialog.run()) {
		Librarian* librarian = dialog.create_librarian();
		combo_box.append(librarian->to_compact_string());
		librarians.push_back(librarian);
	}
}