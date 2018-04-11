#pragma once

#include <vector>
#include <sstream>

#include "asm1492_Date.h"

using namespace std;

class Librarian;
class Customer;
class Transaction_Item;
class Media;
class Bundle;

class Transaction {
public:
	Transaction(int trans_num, Date check_out, Librarian* lib, Customer* cust, vector<Media*> media, vector<Bundle*> bundle);

	string to_string();

private:
	int transaction_number;
	Date check_out_date;
	Librarian* librarian;
	Customer* customer;
	vector<Transaction_Item*> items;
};