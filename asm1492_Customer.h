#pragma once

#include <sstream>
#include <set>

#include "json/asm1492_json.h"

using namespace std;

class Transaction_Item;
class Media;
class Bundle;
class Date;

class Customer {
public:
	Customer(string name_, int id_, long phone_, string email_, double balance_ = 0.0) 
		: name(name_), id(id_), phone(phone_), email(email_), balance(balance_) {};

	bool can_check_out(Media* media);
	bool can_check_out(Bundle* bundle);
	bool has_overdue_items();

	void add_transaction_item(Transaction_Item item);
	void remove_transaction_item(Media* media, Date check_in);
	void remove_transaction_item(Bundle* bundle, Date check_in);

	void pay_balance() { balance = 0.0; };

	string to_string();
	string to_compact_string();

	void save(Json::Value&);

	string get_name() { return name; };
	int get_id() { return id; };
	long get_phone() { return phone; };
	string get_email() { return email; };
	double get_balance() { return balance; };
	vector<Transaction_Item> get_checked_out_items() { return checked_out_items; };
	
private:
	string name;
	int id;
	long phone;
	string email;
	double balance;
	vector<Transaction_Item> checked_out_items;
};