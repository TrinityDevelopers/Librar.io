#include "asm1492_Date_Selection.h"

Date_Selection::Date_Selection() 
	: selected_date(Date::get_current_date()), date_button(selected_date.to_string()), 
	  popover(date_button) {
	
	pack_start(date_button);

	date_button.set_image_from_icon_name("x-office-calendar");
	date_button.signal_toggled().connect(sigc::mem_fun(*this, &Date_Selection::date_toggled));

	popover.add(date_select);
	popover.set_position(Gtk::POS_TOP);
	popover.set_border_width(6);
	popover.set_modal(false);

	date_select.signal_day_selected().connect(sigc::mem_fun(*this, &Date_Selection::date_selected));
	date_select.show();
}

void Date_Selection::date_toggled() {
	popover.set_visible(date_button.get_active());
}

void Date_Selection::date_selected() {
	guint year, month, day;
	date_select.get_date(year, month, day);
	selected_date.set_date(year, month + 1, day);
	date_button.set_label(selected_date.to_string());
}