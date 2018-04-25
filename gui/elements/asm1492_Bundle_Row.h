#pragma once

#include "asm1492_Catalog_Row.h"

#include "../../asm1492_Bundle.h"

class Bundle_Row : public Catalog_Row {
public:
	Bundle_Row(Bundle* bundle_, Date due_date = Date::empty_date);
	Bundle* get_bundle() { return bundle; };
	
private:
	Bundle* bundle;
};