#include "asm1492_List_Entry.h"


List_Entry::List_Entry(const Glib::ustring& hint)
	: Box(Gtk::ORIENTATION_VERTICAL), label_hint(hint), new_entry("New " + hint), delete_entry("Delete " + hint) {
	
	pack_start(controls);

	new_entry.set_image_from_icon_name("list-add");
	controls.pack_start(new_entry);
	new_entry.signal_clicked().connect(sigc::mem_fun(*this, &List_Entry::add_new_entry));

	delete_entry.set_image_from_icon_name("list-remove");
	controls.pack_start(delete_entry);
	delete_entry.signal_clicked().connect(sigc::mem_fun(*this, &List_Entry::delete_last_entry));

	controls.set_layout(Gtk::BUTTONBOX_EXPAND);

	add_new_entry();
}

void List_Entry::clear() {
	for(Clearable_Entry* entry : entries) 
		remove(*entry);
	entries.clear();
	add_new_entry();
}

vector<string> List_Entry::get_string_list() {
	vector<string> ret;
	for(Clearable_Entry* entry : entries)
		ret.push_back(entry->get_text());
	return ret;
}

vector<int> List_Entry::get_int_list() {
	vector<int> ret;
	for(Clearable_Entry* entry : entries)
		ret.push_back(entry->get_int());
	return ret;
}

void List_Entry::add_new_entry() {
	Clearable_Entry* entry = Gtk::manage(new Clearable_Entry());
	entry->set_placeholder_text(label_hint);
	remove(controls);
	pack_start(*entry);
	pack_start(controls);
	entries.push_back(entry);
	show_all();
}

void List_Entry::delete_last_entry() {
	remove(*entries.back());
	entries.pop_back();
}