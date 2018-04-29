#include "asm1492_Main_Window.h"

#include "dialogs/asm1492_Add_Media_Dialog.h"
#include "dialogs/asm1492_Add_Bundle_Dialog.h"
#include "dialogs/asm1492_Browse_Catalog_Dialog.h"
#include "dialogs/asm1492_Create_Account_Dialog.h"
#include "dialogs/asm1492_Check_Out_Dialog.h"
#include "dialogs/asm1492_Check_In_Dialog.h"
#include "dialogs/asm1492_Transaction_Dialog.h"
#include "dialogs/asm1492_Pay_Balance_Dialog.h"
#include "dialogs/asm1492_Load_Dialog.h"
#include "dialogs/asm1492_Save_Dialog.h"
#include "asm1492_Login_Window.h"
#include "asm1492_User_Window.h"
#include "../asm1492_Library.h"

Main_Window::Main_Window() {
	/*: add_media_button("Add Media"), add_bundle_button("Add Bundle"), browse_catalog_button("Browse Catalog"), 
		create_librarian_button("Add Librarian"), create_customer_button("Add Customer"), check_out_button("Check Out"), check_in_button("Check In"), 
		pay_balance_button("Pay Balance") {*/
	
	set_icon_name("accessories-dictionary");

	login_window = NULL;
	user_window = NULL;
	logout();

	/*add(vbox);
	vbox.pack_start(button_box, Gtk::PACK_SHRINK);

	button_box.set_row_spacing(20);
	button_box.set_column_spacing(20);
	button_box.set_column_homogeneous(true);
	button_box.set_border_width(40);*/
	
	add_action("new", sigc::mem_fun(*this, &Main_Window::new_library));
	add_action("open", sigc::mem_fun(*this, &Main_Window::open_library));
	add_action("save", sigc::mem_fun(*this, &Main_Window::save_menu));
	add_action("saveas", sigc::mem_fun(*this, &Main_Window::save_as_menu));
	add_action("exit", sigc::mem_fun(*this, &Main_Window::exit_library));
	add_action("about", sigc::mem_fun(*this, &Main_Window::about));

	/*button_box.attach(add_media_button, 0, 0, 1, 1);
	add_media_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::add_media_button_clicked));

	button_box.attach(add_bundle_button, 1, 0, 1, 1);
	add_bundle_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::add_bundle_button_clicked));

	button_box.attach(browse_catalog_button, 2, 0, 1, 1);
	browse_catalog_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::browse_catalog_button_clicked));

	button_box.attach(create_librarian_button, 3, 0, 1, 1);
	create_librarian_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::create_librarian_button_clicked));

	button_box.attach(create_customer_button, 0, 1, 1, 1);
	create_customer_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::create_customer_button_clicked));

	button_box.attach(check_out_button, 1, 1, 1, 1);
	check_out_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::check_out_button_clicked));

	button_box.attach(check_in_button, 2, 1, 1, 1);
	check_in_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::check_in_button_clicked));

	button_box.attach(pay_balance_button, 3, 1, 1, 1);
	pay_balance_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_Window::pay_balance_button_clicked));*/

	//show_all_children();
}

void Main_Window::login(User* user) {
	login_window->set_inactive();
	remove();
	delete login_window;
	login_window = NULL;
	switch(user->get_type()) {
		case User::Type::Administrator: {
			user_window = Gtk::manage(new Administrator_Window(*this, user));
			break;
		}
		case User::Type::Librarian: {
			user_window = Gtk::manage(new Librarian_Window(*this, user));
			break;
		}
		case User::Type::Customer: {
			user_window = Gtk::manage(new Customer_Window(*this, user));
			break;
		}
	}
	add(*user_window);
}

void Main_Window::logout() {
	if(user_window != NULL) {
		user_window->set_inactive();
		remove();
		delete user_window;
		user_window = NULL;
	}
	if(login_window == NULL) {
		login_window = Gtk::manage(new Login_Window(*this));
		add(*login_window);
	}
}

bool Main_Window::on_delete_event(GdkEventAny* any_event) {
	return !prompt_save();
}

void Main_Window::exit_library() {
	if(prompt_save())
		hide();
}

void Main_Window::new_library() {
	if(prompt_save())
		Library::delete_library();
}

void Main_Window::open_library() {
	Load_Dialog dialog(*this);
	if(dialog.run()) {
		if(prompt_save()) {
			logout();
			Library::delete_library();
			Library::get_instance()->load(dialog.get_file()->get_path());
		}
	}
}

bool Main_Window::prompt_save() {
	if(!Library::get_instance()->is_saved()) {
		string name = Library::get_instance()->get_name();
		Gtk::MessageDialog dialog(*this, "Are you sure you want to close " + name + " without saving?", false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_NONE);
		dialog.set_secondary_text("If you don't save it, changes made to " + name + " will be lost.");
		dialog.add_button("Save", 1);
		dialog.add_button("Don't Save", 2);
		dialog.add_button("Cancel", 0);

		switch(dialog.run()) {
			case 0:
				return false;
			case 1:
				return save();
		}	
	}
	return true;
}

bool Main_Window::save() {
	if(Library::get_instance()->has_file_path()) {
		Library::get_instance()->save(Library::get_instance()->get_path());
		return true;
	}
	else
		return save_as();
}

bool Main_Window::save_as() {
	Save_Dialog dialog(*this);
	if(dialog.run()) {
		Library::get_instance()->save(dialog.get_current_path());
		return true;
	}
	return false;
}

void Main_Window::about() {
	Gtk::AboutDialog* dialog = new Gtk::AboutDialog();
	dialog->set_program_name("Librar.io");
	dialog->set_version("1.0.0");
	dialog->set_copyright("(C) 2018 Virtualoso");
	dialog->set_comments("Program to manage library users and items.");
	dialog->set_license_type(Gtk::LICENSE_GPL_2_0);
	dialog->set_website("http://www.github.com/Virtualoso");
	dialog->set_website_label("Virtualoso Github");
	dialog->set_authors({"Andrew Miller"});
	dialog->set_documenters({"Andrew Miller"});
	dialog->set_artists({"Andrew Miller"});
	dialog->set_logo(Gdk::Pixbuf::create_from_file("assets/librar.io.png"));
	dialog->set_transient_for(*this);
	dialog->run();
	dialog->hide();
}

/*void Main_Window::add_media_button_clicked() {
	Add_Media_Dialog dialog(*this);
	if(dialog.run())
		dialog.create_media();
}

void Main_Window::add_bundle_button_clicked() {
	Add_Bundle_Dialog dialog(*this);
	if(dialog.run())
		dialog.create_bundle();
}

void Main_Window::browse_catalog_button_clicked() {
	Browse_Catalog_Dialog dialog(*this);
	dialog.run();
}

void Main_Window::create_librarian_button_clicked() {
	Create_Librarian_Dialog dialog(*this);
	if(dialog.run())
		dialog.create_librarian();
}

void Main_Window::create_customer_button_clicked() {
	Create_Customer_Dialog dialog(*this);
	if(dialog.run())
		dialog.create_customer();
}

void Main_Window::check_out_button_clicked() {
	Check_Out_Dialog dialog(*this);
	if(dialog.run()) {
		Transaction_Dialog trans_dialog(*this, dialog.create_transaction());
		trans_dialog.run();
	}
}

void Main_Window::check_in_button_clicked() {
	Check_In_Dialog dialog(*this);
	if(dialog.run())
		dialog.check_in();
}

void Main_Window::pay_balance_button_clicked() {
	Pay_Balance_Dialog dialog(*this);
	if(dialog.run())
		dialog.pay_balance();
}*/