#pragma once

#include "json/asm1492_json.h"
#include "asm1492_Date.h"

#include <sstream>
#include <set>

class Bundle;
class Media;

class Transaction_Item {
public:
	enum class Type : unsigned char {
		MEDIA,
		BUNDLE
	};

	Transaction_Item(Bundle* bundle_, Date due_date_) : type(Type::BUNDLE), bundle(bundle_), media(NULL), due_date(due_date_) {};
	Transaction_Item(Media* media_, Date due_date_) : type(Type::MEDIA), bundle(NULL), media(media_), due_date(due_date_) {};

	bool is_overdue(Date current = Date::get_current_date());
	double calculate_fee(Date check_in);

	string to_string();

	bool contains(Bundle* bundle_);
	bool contains(Media* media_);

	void save(Json::Value&);
	static Transaction_Item load(Json::Value&);

	Type get_type() { return type; };
	Bundle* get_bundle() { return bundle; };
	Media* get_media() { return media; };
	Date get_due_date() { return due_date; };

private:
	Type type;
	Bundle* bundle;
	Media* media;
	Date due_date;
};