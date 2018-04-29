#pragma once

#include <string>
#include <vector>

#include "asm1492_User.h"
#include "asm1492_Date.h"

using namespace std;

class Date;
class Customer;
class Media;
class Bundle;
class Transaction;

class Librarian : public User {
public:
	Librarian(string name_, int id_, string p_hex) : User(User::Type::Librarian, name_, id_, p_hex) {};

	Transaction* check_out(Customer* customer, vector<Media*> medias, vector<Bundle*> bundles, Date check_out = Date::get_current_date());
	void check_in(Customer* customer, vector<Media*> medias, vector<Bundle*> bundles, Date check_in = Date::get_current_date());
};