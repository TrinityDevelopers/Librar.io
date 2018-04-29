#pragma once

#include <string>

#include "json/asm1492_json.h"

using namespace std;

class User {
public:
	enum class Type : unsigned char {
		Customer,
		Librarian,
		Administrator
	};

	User(Type type_, string name_, int id_, string p_hex) : type(type_), name(name_), id(id_), pass_hex(p_hex) {};

	virtual void save(Json::Value&);

	string to_compact_string();
	virtual string to_string();

	Type get_type() { return type; };
	string get_name() { return name; };
	int get_id() { return id; };
	string get_pass_hex() { return pass_hex; };

	static string string_from_type(Type type_);
	static Type type_from_string(string type_string);

protected:
	Type type;
	string name;
	int id;
	string pass_hex;
};