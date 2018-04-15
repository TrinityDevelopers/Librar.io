#pragma once

#include <gtkmm.h>

#include "asm1492_Clearable_Entry.h"
#include "asm1492_List_Entry.h"

class Input_Frame : public Gtk::Frame {
public:
	Input_Frame(const Glib::ustring& label, Clearable_Entry* input);
	Input_Frame(const Glib::ustring& label, List_Entry* input);
	Input_Frame(const Glib::ustring& label, Gtk::Widget* input);
	void clear_and_show();

private:
	Clearable_Input* entry;
};