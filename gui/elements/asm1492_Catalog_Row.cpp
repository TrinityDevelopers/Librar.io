#include "asm1492_Catalog_Row.h"

Catalog_Row::Catalog_Row(Type type_) : type(type_) {
	title.set_halign(Gtk::ALIGN_START);
	availability.set_halign(Gtk::ALIGN_START);
	genre.set_halign(Gtk::ALIGN_START);
	id_num.set_halign(Gtk::ALIGN_START);
	medias.set_halign(Gtk::ALIGN_START);
	date.set_halign(Gtk::ALIGN_START);

	Gtk::Frame* frame = Gtk::manage(new Gtk::Frame());
	add(*frame);
	Gtk::Box* hbox = Gtk::manage(new Gtk::Box());
	frame->add(*hbox);
	hbox->pack_start(left_box, Gtk::PACK_SHRINK);
	hbox->pack_start(right_box);
	left_box.set_size_request(140, 80);
	show_all_children();
}