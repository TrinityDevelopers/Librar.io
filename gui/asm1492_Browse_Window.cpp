#include "asm1492_Browse_Window.h"

#include "asm1492_Media_Row.h"

Browse_Window::Browse_Window(bool select) : vbox(Gtk::ORIENTATION_VERTICAL), selectable(select) {
	add(vbox);
	vbox.pack_start(medias);

	Gtk::Label* empty = Gtk::manage(new Gtk::Label("No Media Items"));
	medias.set_placeholder(*empty);

	if(selectable)
		medias.set_selection_mode(Gtk::SELECTION_MULTIPLE);

	set_size_request(400, 400);
	show_all_children();
}

void Browse_Window::add_row(Gtk::ListBoxRow* unmanaged_row) {
	Gtk::ListBoxRow* row = Gtk::manage(unmanaged_row);
	medias.append(*row);
	row->show();
}

vector<Media*> Browse_Window::get_selected_media() {
	vector<Media*> media_list;
	if(selectable)
		for(Gtk::ListBoxRow* row : medias.get_selected_rows())
			media_list.push_back(((Media_Row*) row)->get_media());
	return media_list;
}