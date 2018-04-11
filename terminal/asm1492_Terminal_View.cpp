#include "asm1492_Terminal_View.h"

#include "../asm1492_Library.h"
#include "../asm1492_Bundle.h"
#include "../asm1492_Customer.h"
#include "../asm1492_Librarian.h"
#include "../asm1492_Transaction.h"
#include "../asm1492_Transaction_Item.h"
#include "asm1492_Menu_Function.h"

void Terminal_View::print_menu(vector<Menu_Function*> functions) {
	system("clear");
	cout << 
R"(
______________________________
|Librar.io Terminal Interface|
‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
Please make a selection from the following options:
)";

	for(int i = 0; i < functions.size(); i++)
		cout << i+1 << ") " << functions[i]->get_name() << endl;
	cout << "?" << endl;
}

void Terminal_View::print_catalog() {
	cout << "All Library Media:" << endl << endl;
	for(Media* media : library->get_all_medias())
		cout << *media << endl;

	cout << endl << "All Library Bundles:" << endl << endl;
	for(Bundle* bundle : library->get_all_bundles())
		cout << *bundle << endl;
}

void Terminal_View::print_customer(Customer* cust) {
	cout << "Customer Information:" << endl << endl;
	cout << cust->to_string() << endl;
}

void Terminal_View::print_librarian(Librarian* lib) {
	cout << "Librarian Information:" << endl << endl;
	cout << lib->to_string() << endl;
}

void Terminal_View::print_transaction(Transaction* trans) {
	cout << endl << "Check-Out Reciept:" << endl << endl;
	cout << trans->to_string() << endl;
}

void Terminal_View::print_items(set<Transaction_Item*> items) {
	cout << "Currently Checked-Out Items:" << endl << endl;
	for(Transaction_Item* item : items)
		cout << item->to_string() << endl;
}

void Terminal_View::pay_balance() {
	cout << "Balance Paid!" << endl;
}

void Terminal_View::prompt_for(string argument) {
	cout << "Please input " << argument << ":" << endl;
}

void Terminal_View::prompt_for_date(string argument) {
	cout << "Please input " << argument << " date using the format YYYY MM DD (or leave blank to use current date)" << endl;
}

void Terminal_View::pause() {
	cin.clear();
	cin.sync();
	cout << "Press ENTER to continue:";
	cin.get();
}

void Terminal_View::invalid() {
	cout << "Invalid Input!" << endl;
}

void Terminal_View::exit() {
	cout << "Thanks for using Librar.io!" << endl;
}