#pragma once

#include <gtkmm.h>
#include "../../asm1492_Date.h"

class Date_Selection : public Gtk::Box {
public:
	Date_Selection();
	Date get_date() { return selected_date; };
	
private:
	void date_toggled();
	void date_selected();

	Date selected_date;
	Gtk::ToggleButton date_button;
	Gtk::Popover popover;
	Gtk::Calendar date_select;
};