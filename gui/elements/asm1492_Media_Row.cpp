#include "asm1492_Media_Row.h"

Media_Row::Media_Row(Media* media_, Date due_date) : Catalog_Row(Type::MEDIA), media(media_) {
	title.set_markup("<markup><b>" + media->get_title() + "</b></markup>");
	genre.set_markup("<markup><small>Genre: <b> " + media->get_genre() + "</b></small></markup>");
	availability.set_markup("<markup><small>Availability: <b> " + (media->is_checked_out() ? string("Checked Out") : string("Checked In")) + "</b></small></markup>");
	id_num.set_markup("<markup><small>" + to_string(media->get_id_number()) + "</small></markup>");
	format.set_markup("<markup><small>" + Media::format_to_string(media->get_format()) + "</small></markup>");
	format_icon.set(Media::icon_from_format(media->get_format()));
	
	left_box.pack_start(id_num, Gtk::PACK_SHRINK);
	Gtk::Box* format_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	format_box->pack_start(format, Gtk::PACK_SHRINK);
	format_box->pack_start(format_icon, Gtk::PACK_SHRINK);
	left_box.pack_start(*format_box, Gtk::PACK_EXPAND_PADDING);
	right_box.pack_start(title);
	right_box.pack_start(genre);
	right_box.pack_start(availability);

	if(Date::empty_date < due_date) {
		date.set_markup("<markup><small>Due Date: <b> " + due_date.to_string() + "</b></small></markup>");
		right_box.pack_start(date);
	}
}