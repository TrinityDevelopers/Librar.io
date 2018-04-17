#include "asm1492_Bundle_Row.h"

Bundle_Row::Bundle_Row(Bundle* bundle) {
	name.set_markup("<markup><b>" + bundle->get_name() + "</b></markup>");
	medias.set_markup("<markup><small>Contained Media: <b>" + bundle->get_medias_string() + "</b></small></markup>");
	medias.set_line_wrap();
	availability.set_markup("<markup><small>Availability: <b> " + (bundle->is_checked_out() ? string("Checked Out") : string("Checked In")) + "</b></small></markup>");
	format.set_markup("<markup><small>Bundle</small></markup>");
	format_icon.set(Gtk::IconTheme::get_default()->load_icon("applications-multimedia", 32));
	name.set_halign(Gtk::ALIGN_START);
	medias.set_halign(Gtk::ALIGN_START);
	availability.set_halign(Gtk::ALIGN_START);

	Gtk::Frame* frame = Gtk::manage(new Gtk::Frame());
	add(*frame);
	Gtk::Box* hbox = Gtk::manage(new Gtk::Box());
	frame->add(*hbox);
	Gtk::Box* left_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	Gtk::Box* right_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	hbox->pack_start(*left_box, Gtk::PACK_SHRINK);
	hbox->pack_start(*right_box);
	left_box->set_size_request(140, 80);
	Gtk::Box* format_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	format_box->pack_start(format, Gtk::PACK_SHRINK);
	format_box->pack_start(format_icon, Gtk::PACK_SHRINK);
	left_box->pack_start(*format_box, Gtk::PACK_EXPAND_PADDING);
	right_box->pack_start(name);
	right_box->pack_start(medias);
	right_box->pack_start(availability);
	show_all_children();
}