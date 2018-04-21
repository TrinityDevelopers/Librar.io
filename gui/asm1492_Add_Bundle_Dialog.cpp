#include "asm1492_Add_Bundle_Dialog.h"

#include "asm1492_Media_Row.h"
#include "../asm1492_Library.h"

Add_Bundle_Dialog::Add_Bundle_Dialog(Gtk::Window& parent)
	: Gtk::Dialog("Add Bundle", parent), medias(true) {
	
	set_resizable(false);

	name.set_placeholder_text("Name");
	Input_Frame* frame = Gtk::manage(new Input_Frame("Bundle Name", &name));
	get_content_area()->pack_start(*frame);

	Gtk::Box* box = Gtk::manage(new Gtk::Box());
	get_content_area()->pack_start(*box);
	Gtk::Box* box_left = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	box->pack_start(*box_left);
	Gtk::Frame* media_frame = Gtk::manage(new Gtk::Frame("Medias"));
	box_left->pack_start(*media_frame);
	Gtk::Box* media_box = Gtk::manage(new Gtk::Box());
	media_box->set_border_width(10);
	media_box->pack_start(medias);
	media_frame->add(*media_box);

	for(Media* media : Library::get_instance()->get_all_medias())
		medias.add_row(new Media_Row(media));

	add_button("_Cancel", 0);
	add_button("_OK", 1);

	get_action_area()->set_layout(Gtk::BUTTONBOX_EXPAND);

	show_all_children();
}

Bundle* Add_Bundle_Dialog::create_bundle() {
	return Library::get_instance()->create_new_bundle(name.get_text(), medias.get_selected_media());
}