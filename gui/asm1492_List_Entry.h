#pragma once

#include <gtkmm.h>
#include <vector>

#include "asm1492_Clearable_Input.h"

using namespace std;

class List_Entry : public Gtk::Box, public Clearable_Input {
public:
	List_Entry(const Glib::ustring& hint);
	virtual ~List_Entry() {};
	void clear();
private:
	void add_new_entry();
	void delete_last_entry();

	Glib::ustring label_hint;
	Gtk::ButtonBox controls;
	Gtk::Button new_entry;
	Gtk::Button delete_entry;
	vector<Gtk::Entry*> entries;
};