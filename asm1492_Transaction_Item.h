#pragma once

#include "asm1492_Date.h"

#include <sstream>
#include <set>

class Bundle;
class Media;

class Transaction_Item {
public:
	Transaction_Item(Bundle* bundle_, Date due_date_) : bundle(bundle_), media(NULL), due_date(due_date_) {};
	Transaction_Item(Media* media_, Date due_date_) : bundle(NULL), media(media_), due_date(due_date_) {};

	bool is_overdue(Date current = Date::get_current_date());
	double calculate_fee(Date check_in);

	string to_string();

	bool contains(Bundle* bundle_);
	bool contains(Media* media_);

private:
	Bundle* bundle;
	Media* media;
	Date due_date;
};