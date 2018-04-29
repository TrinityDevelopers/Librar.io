#include "asm1492_User.h"

void User::save(Json::Value& user) {
	user["type"] = string_from_type(type);
	user["name"] = name;
	user["pass_hex"] = pass_hex;
}

string User::to_compact_string() {
	stringstream stm;
	stm << name << ", ID# " << id;
	return stm.str();
}

string User::to_string() {
	stringstream stm;
	stm << "Name:         " << name << endl;
	stm << "ID Number:    " << id << endl;
	return stm.str();
}

string User::string_from_type(Type type_) {
	switch(type_) {
		case Type::Administrator:
			return "Administrator";
		case Type::Librarian:
			return "Librarian";
		case Type::Customer:
			return "Customer";
	}
}

User::Type User::type_from_string(string type_string) {
	if(type_string == "Administrator")
		return Type::Administrator;
	else if(type_string == "Librarian")
		return Type::Librarian;
	else
		return Type::Customer;
}