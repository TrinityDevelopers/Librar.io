#include "asm1492_Bundle_Row.h"

Bundle_Row::Bundle_Row(Bundle* bundle_, Date due_date) : Catalog_Row(Type::BUNDLE), bundle(bundle_) {
	title.set_markup("<markup><b>" + bundle->get_name() + "</b></markup>");
	medias.set_markup("<markup><small>Contained Media: <b>" + bundle->get_medias_string() + "</b></small></markup>");
	medias.set_line_wrap();
	availability.set_markup("<markup><small>Availability: <b> " + (bundle->is_checked_out() ? string("Checked Out") : string("Checked In")) + "</b></small></markup>");
	format.set_markup("<markup><small>Bundle</small></markup>");
	format_icon.set(Gtk::IconTheme::get_default()->load_icon("applications-multimedia", 32));
	
	Gtk::Box* format_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	format_box->pack_start(format, Gtk::PACK_SHRINK);
	format_box->pack_start(format_icon, Gtk::PACK_SHRINK);
	left_box.pack_start(*format_box, Gtk::PACK_EXPAND_PADDING);
	right_box.pack_start(title);
	right_box.pack_start(medias);
	right_box.pack_start(availability);

	if(Date::empty_date < due_date) {
		date.set_markup("<markup><small>Due Date: <b> " + due_date.to_string() + "</b></small></markup>");
		right_box.pack_start(date);
	}
}