#include "asm1492_User_Window.h"

#include "asm1492_Main_Window.h"

User_Window::User_Window(Main_Window& parent_, User* user_) : Gtk::Box(Gtk::ORIENTATION_VERTICAL), parent(parent_), user(user_) {
	parent.add_action("logout", sigc::mem_fun(parent, &Main_Window::logout));
	show_all();
}

void User_Window::set_inactive() {
	parent.remove_action("logout");
}

Administrator_Window::Administrator_Window(Main_Window& parent_, User* admin) : User_Window(parent_, admin) {
	parent.set_title("Librar.io - Administrator");
}

void Administrator_Window::set_inactive() {
	User_Window::set_inactive();
}

Librarian_Window::Librarian_Window(Main_Window& parent_, User* librarian) : User_Window(parent_, librarian) {
	parent.set_title("Librar.io - Librarian");
}

void Librarian_Window::set_inactive() {
	User_Window::set_inactive();
}

Customer_Window::Customer_Window(Main_Window& parent_, User* customer) : User_Window(parent_, customer) {
	parent.set_title("Librar.io - Customer");
}

void Customer_Window::set_inactive() {
	User_Window::set_inactive();
}