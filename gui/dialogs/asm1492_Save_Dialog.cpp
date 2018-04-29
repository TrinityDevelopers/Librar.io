#include "asm1492_Save_Dialog.h"

Save_Dialog::Save_Dialog(Gtk::Window& parent) : Gtk::FileChooserDialog(parent, "Save Library File", Gtk::FILE_CHOOSER_ACTION_SAVE) {
	auto filter = Gtk::FileFilter::create();
	filter->add_pattern("*.ldb");
	filter->set_name("Librar.io DB File (.ldb)");
	add_filter(filter);

	add_button("Cancel", 0);
	save_button = add_button("Save", 1);
	set_default_response(1);
}

string Save_Dialog::get_current_path() {
	string path = get_current_folder_file()->get_path();
	string file_name = get_current_name();
	if(file_name.find(".ldb") == string::npos)
		file_name += ".ldb";
	return path + "/" + file_name;
}