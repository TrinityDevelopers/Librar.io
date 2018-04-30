#include "asm1492_Login_Window.h"

#include "asm1492_Main_Window.h"
#include "../asm1492_User.h"
#include "../asm1492_picosha2.h"
#include "../asm1492_Library.h"
#include "dialogs/asm1492_Create_Account_Dialog.h"

Login_Window::Login_Window(Main_Window& parent_) : Gtk::Box(Gtk::ORIENTATION_VERTICAL), parent(parent_), create_account_button("Create Account"), login_button("Login") {
	parent.set_title("Librar.io - Login");
	parent.add_action("add_account", sigc::mem_fun(*this, &Login_Window::create_account));

	Gtk::Box* input_box = Gtk::manage(new Gtk::Box());
	pack_start(*input_box, Gtk::PACK_EXPAND_PADDING);
	Gtk::Frame* frame = Gtk::manage(new Gtk::Frame());
	input_box->pack_start(*frame, Gtk::PACK_EXPAND_PADDING);
	set_border_width(5);
	input_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	input_box->set_border_width(5);
	frame->add(*input_box);
	logo.set("assets/librar.io.png");
	input_box->pack_start(logo, Gtk::PACK_SHRINK);

	input_box->pack_start(invalid_label, Gtk::PACK_SHRINK);

	id.set_placeholder_text("7-Digit ID#");
	id.set_activates_default();
	id.set_input_purpose(Gtk::INPUT_PURPOSE_PIN);
	Input_Frame* iframe = Gtk::manage(new Input_Frame("Library ID Number", &id));
	input_box->pack_start(*iframe);

	password.set_placeholder_text("Password");
	password.set_activates_default();
	password.set_input_purpose(Gtk::INPUT_PURPOSE_PASSWORD);
	password.set_visibility(false);
	password.set_icon_from_icon_name("dialog-password", Gtk::ENTRY_ICON_SECONDARY);
	password.signal_icon_press().connect(sigc::mem_fun(*this, &Login_Window::password_show));
	password.signal_icon_release().connect(sigc::mem_fun(*this, &Login_Window::password_hide));
	iframe = Gtk::manage(new Input_Frame("Password", &password));
	input_box->pack_start(*iframe);

	login_button.set_image_from_icon_name("emblem-default");
	login_button.signal_clicked().connect(sigc::mem_fun(*this, &Login_Window::do_login));
	create_account_button.set_image_from_icon_name("contact-new");
	create_account_button.signal_clicked().connect(sigc::mem_fun(*this, &Login_Window::create_account));

	Gtk::ButtonBox* button_box = Gtk::manage(new Gtk::ButtonBox());
	button_box->set_layout(Gtk::BUTTONBOX_EDGE);
	button_box->pack_start(create_account_button);
	button_box->pack_start(login_button);
	input_box->pack_start(*button_box);

	login_button.set_can_default();
	parent.set_default(login_button);
	
	show_all_children();
	invalid_label.hide();
	show();
}

void Login_Window::set_inactive() {
	parent.remove_action("add_account");
	hide();
}

void Login_Window::do_login() {
	invalid_label.hide();
	if(!id.get_text().empty() && !password.get_text().empty()) {
		User* user = Library::get_user(id.get_int());
		if(user != NULL) {
			if(picosha2::hash256_hex_string(password.get_text()) == user->get_pass_hex()) {
				parent.login(user);
			} else {
				invalid_label.set_markup("<span foreground='red'>Invalid ID number/Password</span>");
				invalid_label.show();
			}
		} else {
			invalid_label.set_markup("<span foreground='red'>Invalid ID number</span>");
			invalid_label.show();
		}
	} else {
		invalid_label.set_markup("<span foreground='red'>Please input an ID number and Password</span>");
		invalid_label.show();
	}
}

void Login_Window::create_account() {
	Create_Account_Dialog dialog(parent);
	if(dialog.run())
		dialog.create_account();
}