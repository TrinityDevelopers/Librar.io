#include "asm1492_Media_View.h"

#include "../asm1492_User_Window.h"
#include "../../asm1492_Library.h"

Media_View::Media_View(User_Window& parent, Media* media_) : Gtk::Box(Gtk::ORIENTATION_VERTICAL), media(media_) {
	Gtk::Box* internal_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	internal_box->set_border_width(2);
	Gtk::Frame* outline = Gtk::manage(new Gtk::Frame());
	outline->add(*internal_box);
	pack_start(*outline);
	Gtk::Box* box = Gtk::manage(new Gtk::Box());
	close.set_image_from_icon_name("window-close");
	close.set_halign(Gtk::ALIGN_END);
	close.set_valign(Gtk::ALIGN_START);
	close.signal_clicked().connect(sigc::mem_fun(parent, &User_Window::close_dialog));
	Gtk::Label* label = Gtk::manage(new Gtk::Label());
	label->set_markup("<markup><small>" + to_string(media->get_id_number()) + "</small></markup>");
	label->set_halign(Gtk::ALIGN_START);
	label->set_valign(Gtk::ALIGN_START);
	box->pack_start(*label);
	box->pack_start(close);
	internal_box->pack_start(*box);
	label = Gtk::manage(new Gtk::Label());
	label->set_markup("<markup><small>" + Media::format_to_string(media->get_format()) + "</small></markup>");
	Gtk::Image* icon = Gtk::manage(new Gtk::Image(Media::icon_from_format(media->get_format())));
	Gtk::Box* format_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	format_box->pack_start(*label, Gtk::PACK_SHRINK);
	format_box->pack_start(*icon, Gtk::PACK_SHRINK);
	format_box->set_halign(Gtk::ALIGN_CENTER);
	internal_box->pack_start(*format_box, Gtk::PACK_EXPAND_PADDING);
	label = Gtk::manage(new Gtk::Label(media->to_string()));
	label->set_halign(Gtk::ALIGN_START);
	internal_box->pack_start(*label);
	if(media->is_checked_out()) {
		label = Gtk::manage(new Gtk::Label("Checked Out By: " + Library::get_instance()->get_owner(media)->to_compact_string()));
		label->set_halign(Gtk::ALIGN_START);
		internal_box->pack_start(*label);
	}
	show_all();
}