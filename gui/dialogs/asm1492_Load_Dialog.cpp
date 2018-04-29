#include "asm1492_Load_Dialog.h"

Load_Dialog::Load_Dialog(Gtk::Window& parent) : Gtk::FileChooserDialog(parent, "Open Library File") {
	auto filter = Gtk::FileFilter::create();
	filter->add_pattern("*.ldb");
	filter->set_name("Librar.io DB File (.ldb)");
	add_filter(filter);

	add_button("Cancel", 0);
	open_button = add_button("Open", 1);
	set_default_response(1);

	signal_selection_changed().connect(sigc::mem_fun(*this, &Load_Dialog::update_open_button));
}

void Load_Dialog::update_open_button() {
	if(get_file() && get_file()->query_file_type() == Gio::FILE_TYPE_REGULAR)
		open_button->set_sensitive();
	else
		open_button->set_sensitive(false);
}