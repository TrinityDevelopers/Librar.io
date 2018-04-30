#include "asm1492_Bundle_View.h"

#include "../asm1492_User_Window.h"
#include "../../asm1492_Library.h"

Bundle_View::Bundle_View(User_Window& parent, Bundle* bundle_) : Gtk::Box(Gtk::ORIENTATION_VERTICAL), bundle(bundle_) {
	Gtk::Box* internal_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	internal_box->set_border_width(2);
	Gtk::Frame* outline = Gtk::manage(new Gtk::Frame());
	outline->add(*internal_box);
	pack_start(*outline);
	close.set_image_from_icon_name("window-close");
	close.set_halign(Gtk::ALIGN_END);
	close.set_valign(Gtk::ALIGN_START);
	close.signal_clicked().connect(sigc::mem_fun(parent, &User_Window::close_dialog));
	internal_box->pack_start(close);
	Gtk::Label* label = Gtk::manage(new Gtk::Label());
	label->set_markup("<markup><small>Bundle</small></markup>");
	Gtk::Image* icon = Gtk::manage(new Gtk::Image());
	icon->set_from_icon_name("applications-multimedia", Gtk::ICON_SIZE_DND);
	Gtk::Box* format_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	format_box->pack_start(*label, Gtk::PACK_SHRINK);
	format_box->pack_start(*icon, Gtk::PACK_SHRINK);
	internal_box->pack_start(*format_box, Gtk::PACK_EXPAND_PADDING);
	label = Gtk::manage(new Gtk::Label(bundle->to_compact_string()));
	label->set_halign(Gtk::ALIGN_START);
	internal_box->pack_start(*label);
	if(bundle->is_checked_out()) {
		label = Gtk::manage(new Gtk::Label("Checked Out By: " + Library::get_instance()->get_owner(bundle)->to_compact_string()));
		label->set_halign(Gtk::ALIGN_START);
		internal_box->pack_start(*label);
	}
	show_all();
}