#include "asm1492_Input_Frame.h"

Input_Frame::Input_Frame(const Glib::ustring& label, Clearable_Entry* input)
	: Gtk::Frame(label), entry(input) {
	
	Gtk::Box* input_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	input_box->set_border_width(5);
	add(*input_box);
	input_box->add(*input);
}

Input_Frame::Input_Frame(const Glib::ustring& label, List_Entry* input)
	: Gtk::Frame(label), entry(input) {
	
	Gtk::Box* input_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	input_box->set_border_width(5);
	add(*input_box);
	input_box->add(*input);
}

Input_Frame::Input_Frame(const Glib::ustring& label, Gtk::Widget* input)
	: Gtk::Frame(label), entry(NULL) {
	
	Gtk::Box* input_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	input_box->set_border_width(5);
	add(*input_box);
	input_box->add(*input);
}

void Input_Frame::clear_and_show() {
	entry->clear();
	show_all();
}