#pragma once

#include <sstream>
#include <set>

#include "asm1492_User.h"
#include "asm1492_Transaction_Item.h"

using namespace std;

class Media;
class Bundle;
class Date;

class Customer : public User {
public:
	Customer(string name_, int id_, string p_hex, long phone_, string email_, double balance_ = 0.0) 
		: User(Type::Customer, name_, id_, p_hex), phone(phone_), email(email_), balance(balance_) {};

	bool can_check_out(Media* media);
	bool can_check_out(Bundle* bundle);
	bool has_overdue_items();

	void add_transaction_item(Transaction_Item item);
	void remove_transaction_item(Media* media, Date check_in);
	void remove_transaction_item(Bundle* bundle, Date check_in);
	bool is_checked_out(Media* media);
	bool is_checked_out(Bundle* bundle);


	void pay_balance() { balance = 0.0; };

	string to_string();
	string get_balance_string();

	void save(Json::Value&);

	long get_phone() { return phone; };
	string get_email() { return email; };
	double get_balance() { return balance; };
	vector<Transaction_Item> get_checked_out_items() { return checked_out_items; };
	
private:
	long phone;
	string email;
	double balance;
	vector<Transaction_Item> checked_out_items;
};