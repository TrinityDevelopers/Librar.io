#pragma once

#include <gtkmm.h>

#include "asm1492_Clearable_Input.h"

class Clearable_Entry : public Gtk::Entry, public Clearable_Input {
public:
	Clearable_Entry() : Gtk::Entry() {};
	void clear() {
		set_text("");
	}
};