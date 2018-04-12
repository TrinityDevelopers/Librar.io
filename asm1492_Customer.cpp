#include "asm1492_Customer.h"

#include "media/asm1492_Media.h"
#include "asm1492_Bundle.h"
#include "asm1492_Transaction_Item.h"

#include <iomanip>

bool Customer::can_check_out(Media* media) {
	if(media->is_checked_out() || balance > 5.0 || has_overdue_items() || checked_out_items.size() >= 50)
		return false;
	return true;
}

bool Customer::can_check_out(Bundle* bundle) {
	if(bundle->is_checked_out() || balance > 5.0 || has_overdue_items() || checked_out_items.size() >= 50)
		return false;
	return true;
}

bool Customer::has_overdue_items() {
	for(Transaction_Item item : checked_out_items) {
		if(item.is_overdue())
			return true;
	}
	return false;
}

void Customer::add_transaction_item(Transaction_Item item) {
	checked_out_items.push_back(item);
}

void Customer::remove_transaction_item(Media* media, Date check_in) {
	for(auto it = checked_out_items.begin(); it != checked_out_items.end(); ++it){
		if((*it).contains(media)) {
			balance += (*it).calculate_fee(check_in);
			checked_out_items.erase(it);
		}
	}
}

void Customer::remove_transaction_item(Bundle* bundle, Date check_in) {
	for(auto it = checked_out_items.begin(); it != checked_out_items.end(); ++it){
		if((*it).contains(bundle)) {
			balance += (*it).calculate_fee(check_in);
			checked_out_items.erase(it);
		}
	}
}

string Customer::to_string() {
	stringstream stm;
	stm << "Name:         " << name << endl;
	stm << "ID Number:    " << id << endl;
	stm << "Phone Number: " << phone << endl;
	stm << "Email:        " << email << endl;
	stm << "Balance:      " << "$" << setprecision(2) << fixed << balance << endl;
	return stm.str();
}

string Customer::to_compact_string() {
	stringstream stm;
	stm << name << ", ID# " << id;
	return stm.str();
}

void Customer::save(Json::Value& customer) {
	customer["name"] = name;
	customer["phone"] = phone;
	customer["email"] = email;
	customer["balance"] = balance;
	Json::Value items_list;
	for(Transaction_Item trans_item : checked_out_items) {
		Json::Value item;
		trans_item.save(item);
		items_list.append(item);
	}
	customer["checked_out_items"] = items_list;
}