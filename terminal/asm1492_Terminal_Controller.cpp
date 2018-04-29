#include "asm1492_Terminal_Controller.h"

#include "asm1492_Terminal_View.h"
#include "asm1492_Menu_Function.h"
#include "../asm1492_Library.h"
#include "../asm1492_Customer.h"
#include "../asm1492_Librarian.h"
#include "../asm1492_Transaction_Item.h"

#include <sstream>

void Terminal_Controller::run_cli() {
	init();
	int cmd;
	do read_cmd(&cmd);
	while(execute_cmd(cmd));
}

void Terminal_Controller::read_cmd(int* cmd) {
	*cmd = 0;
	view->print_menu(functions);
	cin >> *cmd;
}

bool Terminal_Controller::execute_cmd(int cmd) {
	bool ret = true;
	if(cmd > 0 && cmd < functions.size()+1) {
		cin.ignore();
		ret = (*functions[cmd-1])();
	}
	else
		view->invalid();
	if(ret)
		view->pause();
	return ret;
}

string Terminal_Controller::prompt_for_string(string arg, string def) {
	view->prompt_for(arg);
	getline(cin, def);
	return def;
}

int Terminal_Controller::prompt_for_int(string arg, int def) {
	view->prompt_for(arg);
	string line;
	getline(cin, line);
	istringstream stm(line);
	stm >> def;
	return def;
}

long Terminal_Controller::prompt_for_long(string arg, long def) {
	view->prompt_for(arg);
	string line;
	getline(cin, line);
	istringstream stm(line);
	stm >> def;
	return def;
}

double Terminal_Controller::prompt_for_double(string arg, double def) {
	view->prompt_for(arg);
	string line;
	getline(cin, line);
	istringstream stm(line);
	stm >> def;
	return def;
}

vector<string> Terminal_Controller::prompt_for_string_list(string arg, vector<string> def) {
	view->prompt_for(arg);
	string line;
	getline(cin, line);
	istringstream stm(line);
	string add;
	while(getline(stm, add, ','))
		def.push_back(add);
	return def;
}

vector<int> Terminal_Controller::prompt_for_int_list(string arg, vector<int> def) {
	view->prompt_for(arg);
	string line;
	getline(cin, line);
	istringstream stm(line);
	int add;
	while(stm >> add)
		def.push_back(add);
	return def;
}

Date Terminal_Controller::prompt_for_date(string arg, Date def) {
	int year, month, day;
	view->prompt_for_date(arg);
	string line;
	getline(cin, line);
	istringstream stm(line);
	if(stm >> year >> month >> day)
		return {year, month, day};
	return def;
}

void Terminal_Controller::init() {
	functions.push_back(new Exit_Function(this));
	functions.push_back(new Login_Function(this, "Administrator"));
	functions.push_back(new Login_Function(this, "Librarian"));
	functions.push_back(new Login_Function(this, "Customer"));
	functions.push_back(new Load_Function(this));
	functions.push_back(new Save_Function(this));
}

void Customer_Login_Controller::init() {
	functions.push_back(new Customer_Login_Function(this, "New Customer"));
	for(Customer* cust : library->get_all_customers())
		functions.push_back(new Customer_Login_Function(this, cust->to_compact_string(), cust));
}

void Librarian_Login_Controller::init() {
	functions.push_back(new Librarian_Login_Function(this, "New Librarian"));
	for(Librarian* lib : library->get_all_librarians())
		functions.push_back(new Librarian_Login_Function(this, lib->to_compact_string(), lib));
}

void Admin_Controller::init() {
	functions.push_back(new Logout_Function(this));
	functions.push_back(new Add_Media_Function(this));
	functions.push_back(new Add_Bundle_Function(this));
	functions.push_back(new Delete_Media_Function(this));
	functions.push_back(new Delete_Bundle_Function(this));
	functions.push_back(new Print_Catalog_Function(this));
}

void Librarian_Controller::init() {
	functions.push_back(new Logout_Function(this));
	functions.push_back(new Check_Out_Function(this));
	functions.push_back(new Check_In_Function(this));
	functions.push_back(new Print_Info_Function(this, "Librarian"));
	functions.push_back(new Print_Catalog_Function(this));
}

void Customer_Controller::init() {
	functions.push_back(new Logout_Function(this));
	functions.push_back(new Pay_Balance_Function(this));
	functions.push_back(new Print_Info_Function(this, "Customer"));
	functions.push_back(new Print_Items_Function(this));
	functions.push_back(new Print_Catalog_Function(this));
}