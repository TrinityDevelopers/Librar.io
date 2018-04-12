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

private:
	int transaction_number;
	Date check_out_date;
	Librarian* librarian;
	Customer* customer;
	vector<Transaction_Item> items;
};