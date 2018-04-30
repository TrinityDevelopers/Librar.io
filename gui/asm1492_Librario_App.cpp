#include "asm1492_Librario_App.h"
#include "asm1492_Main_Window.h"

Librario_App::Librario_App() : Gtk::Application("com.virtualoso.librario") {
	Glib::set_application_name("Librar.io");
}

Glib::RefPtr<Librario_App> Librario_App::create() {
	return Glib::RefPtr<Librario_App>(new Librario_App());
}

void Librario_App::on_startup() {
	Gtk::Application::on_startup();

	auto win_menu = Gio::Menu::create();

	auto submenu_file = Gio::Menu::create();
	auto item = Gio::MenuItem::create("_New Library", "win.new");
	item->set_attribute_value("accel", Glib::Variant<Glib::ustring>::create("<Primary>n"));
	submenu_file->append_item(item);
	item = Gio::MenuItem::create("_Open Library", "win.open");
	item->set_attribute_value("accel", Glib::Variant<Glib::ustring>::create("<Primary>o"));
	submenu_file->append_item(item);
	item = Gio::MenuItem::create("_Save", "win.save");
	item->set_attribute_value("accel", Glib::Variant<Glib::ustring>::create("<Primary>s"));
	submenu_file->append_item(item);
	item = Gio::MenuItem::create("_Save As", "win.saveas");
	item->set_attribute_value("accel", Glib::Variant<Glib::ustring>::create("<Ctrl><Shift>s"));
	submenu_file->append_item(item);
	submenu_file->append("_Preferences", "win.preferences");
	auto section_exit = Gio::Menu::create();
	item = Gio::MenuItem::create("_Logout", "win.logout");
	item->set_attribute_value("accel", Glib::Variant<Glib::ustring>::create("<Primary>l"));
	section_exit->append_item(item);
	item = Gio::MenuItem::create("_Exit", "win.exit");
	item->set_attribute_value("accel", Glib::Variant<Glib::ustring>::create("<Primary>q"));
	section_exit->append_item(item);
	submenu_file->append_section(section_exit);
	win_menu->append_submenu("File", submenu_file);

	auto submenu_edit = Gio::Menu::create();
	item = Gio::MenuItem::create("_Undo", "win.undo");
	item->set_attribute_value("accel", Glib::Variant<Glib::ustring>::create("<Primary>z"));
	submenu_edit->append_item(item);
	item = Gio::MenuItem::create("_Redo", "win.redo");
	item->set_attribute_value("accel", Glib::Variant<Glib::ustring>::create("<Primary>y"));
	submenu_edit->append_item(item);
	win_menu->append_submenu("Edit", submenu_edit);

	auto submenu_librario = Gio::Menu::create();
	submenu_librario->append("_Create Account", "win.add_account");
	submenu_librario->append("_Create Media", "win.add_media");
	submenu_librario->append("_Create Bundle", "win.add_bundle");
	submenu_librario->append("_Check Out", "win.check_out");
	submenu_librario->append("_Check In", "win.check_in");
	submenu_librario->append("_Pay Balance", "win.pay_balance");
	win_menu->append_submenu("Librar.io", submenu_librario);

	auto submenu_help = Gio::Menu::create();
	submenu_help->append("_About", "win.about");
	win_menu->append_submenu("Help", submenu_help);

	set_menubar(win_menu);
}

void Librario_App::create_window() {
	Main_Window* window = new Main_Window();
	add_window(*window);

	window->signal_hide().connect(sigc::bind(sigc::mem_fun(*this, &Librario_App::on_window_hide), window));
	window->show();
}

void Librario_App::on_window_hide(Main_Window* window) {
	delete window;
}

void Librario_App::on_activate() {
	create_window();
}