#pragma once

#include <vector>
#include <sstream>

#include "json/asm1492_json.h"
#include "asm1492_Date.h"

using namespace std;

class Librarian;
class Customer;
class Transaction_Item;
class Media;
class Bundle;

class Transaction {
public:
	Transaction(int trans_num, Date check_out, Librarian* lib, Customer* cust)
		: transaction_number(trans_num), check_out_date(check_out), librarian(lib), customer(cust) {};

	void init(vector<Media*> medias, vector<Bundle*> bundles);
	void add_transaction_item(Transaction_Item item);
	string to_string();

	void save(Json::Value&);

	int get_transaction_number() { return transaction_number; };
	Date get_check_out_date() { return check_out_date; };
	Librarian* get_librarian() { return librarian; };
	Customer* get_customer() { return customer; };
	vector<Transaction_Item> get_items() { return items; };

private:
	int transaction_number;
	Date check_out_date;
	Librarian* librarian;
	Customer* customer;
	vector<Transaction_Item> items;
};