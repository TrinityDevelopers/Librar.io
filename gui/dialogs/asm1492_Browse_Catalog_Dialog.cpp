#include "asm1492_Browse_Catalog_Dialog.h"

#include "../../asm1492_Library.h"

#include "../elements/asm1492_Bundle_Row.h"
#include "../elements/asm1492_Media_Row.h"

Browse_Catalog_Dialog::Browse_Catalog_Dialog(Gtk::Window& parent) 
	: Gtk::Dialog("Browse Catalog", parent), box(Gtk::ORIENTATION_HORIZONTAL), box_left(Gtk::ORIENTATION_VERTICAL) {
	
	get_content_area()->pack_start(box);
	box.pack_start(box_left);
	Gtk::Frame* media_frame = Gtk::manage(new Gtk::Frame("Entries"));
	box_left.pack_start(*media_frame);
	Gtk::Box* media_box = Gtk::manage(new Gtk::Box());
	media_box->set_border_width(10);
	media_box->pack_start(medias);
	media_frame->add(*media_box);

	for(Media* media : Library::get_instance()->get_all_medias())
		add_media(media);

	for(Bundle* bundle : Library::get_instance()->get_all_bundles())
		add_bundle(bundle);

	show_all_children();
}

void Browse_Catalog_Dialog::add_media(Media* media) {
	medias.add_row(new Media_Row(media));
}

void Browse_Catalog_Dialog::add_bundle(Bundle* bundle) {
	medias.add_row(new Bundle_Row(bundle));
}