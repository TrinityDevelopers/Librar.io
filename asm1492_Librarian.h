#pragma once

#include <string>
#include <vector>

#include "asm1492_Date.h"

using namespace std;

class Date;
class Customer;
class Media;
class Bundle;
class Transaction;

class Librarian {
public:
	Librarian(string name_, int id_) : name(name_), id(id_) {};

	Transaction* check_out(Customer* customer, vector<Media*> medias, vector<Bundle*> bundles, Date check_out = Date::get_current_date());
	void check_in(Customer* customer, vector<Media*> medias, vector<Bundle*> bundles, Date check_in = Date::get_current_date());

	string to_compact_string();
	string to_string();

	string get_name() { return name; };
	int get_id() { return id; };

private:
	string name;
	int id;
};