#include "asm1492_Browse_Window.h"

#include "asm1492_Media_Row.h"
#include "asm1492_Bundle_Row.h"

Browse_Window::Browse_Window(bool select) : vbox(Gtk::ORIENTATION_VERTICAL), selectable(select) {
	add(vbox);
	vbox.pack_start(medias);

	Gtk::Label* empty = Gtk::manage(new Gtk::Label("No Media Items"));
	medias.set_placeholder(*empty);

	if(selectable)
		medias.set_selection_mode(Gtk::SELECTION_MULTIPLE);

	set_size_request(450, 400);
	show_all_children();
}

void Browse_Window::add_row(Gtk::ListBoxRow* unmanaged_row) {
	Gtk::ListBoxRow* row = Gtk::manage(unmanaged_row);
	medias.append(*row);
	row->show_all();
}

void Browse_Window::clear() {
	medias.unselect_all();
	vector<Gtk::Widget*> children = medias.get_children();
	for(Widget* row : children) {
		medias.remove(*row);
		delete row;
	}
}

vector<Media*> Browse_Window::get_selected_media() {
	vector<Media*> media_list;
	if(selectable)
		for(Gtk::ListBoxRow* row : medias.get_selected_rows())
			if(((Catalog_Row*) row)->get_type() == Catalog_Row::Type::MEDIA)
				media_list.push_back(((Media_Row*) row)->get_media());
	return media_list;
}

vector<Bundle*> Browse_Window::get_selected_bundles() {
	vector<Bundle*> bundle_list;
	if(selectable)
		for(Gtk::ListBoxRow* row : medias.get_selected_rows())
			if(((Catalog_Row*) row)->get_type() == Catalog_Row::Type::BUNDLE)
				bundle_list.push_back(((Bundle_Row*) row)->get_bundle());
	return bundle_list;
}