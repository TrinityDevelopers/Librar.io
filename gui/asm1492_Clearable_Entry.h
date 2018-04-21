#pragma once

#include <gtkmm.h>
#include <sstream>

#include "asm1492_Clearable_Input.h"

using namespace std;

class Clearable_Entry : public Gtk::Entry, public Clearable_Input {
public:
	Clearable_Entry() : Gtk::Entry() {};
	void clear() {
		set_text("");
	}
	int get_int() {
		int ret = 0;
		istringstream stm(get_text());
		stm >> ret;
		return ret;
	}
	long get_long() {
		long ret = 0;
		istringstream stm(get_text());
		stm >> ret;
		return ret;
	}
	double get_double() {
		double ret = 0;
		istringstream stm(get_text());
		stm >> ret;
		return ret;
	}
};