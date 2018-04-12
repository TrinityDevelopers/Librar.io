#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Library;
class Menu_Function;
class Customer;
class Librarian;
class Transaction;
class Transaction_Item;

class Terminal_View {
public:
	Terminal_View(Library* lib) : library(lib) {};

	void print_menu(vector<Menu_Function*> functions);

	void print_catalog();
	void print_customer(Customer* cust);
	void print_librarian(Librarian* lib);
	void print_transaction(Transaction* trans);
	void print_items(vector<Transaction_Item> items);
	void pay_balance();

	void prompt_for(string argument);
	void prompt_for_date(string argument);

	void load();
	void load_fail();
	void save();
	void pause();
	void invalid();
	void exit();

private:
	Library* library;
};