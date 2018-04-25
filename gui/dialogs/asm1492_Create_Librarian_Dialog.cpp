#include "asm1492_Create_Librarian_Dialog.h"

#include "../elements/asm1492_Media_Row.h"
#include "../../asm1492_Library.h"

Create_Librarian_Dialog::Create_Librarian_Dialog(Gtk::Window& parent)
	: Gtk::Dialog("Add Librarian", parent) {
	
	set_resizable(false);
	set_size_request(250);

	name.set_placeholder_text("Name");
	name.set_activates_default();
	Input_Frame* frame = Gtk::manage(new Input_Frame("Librarian Name", &name));
	get_content_area()->pack_start(*frame);

	add_button("_Cancel", 0);
	add_button("_OK", 1);
	set_default_response(1);

	get_action_area()->set_layout(Gtk::BUTTONBOX_EXPAND);

	show_all_children();
}

Librarian* Create_Librarian_Dialog::create_librarian() {
	return Library::get_instance()->create_new_librarian(name.get_text());
}