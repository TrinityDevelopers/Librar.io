#include "asm1492_Menu_Function.h"

#include "asm1492_Terminal_Controller.h"
#include "asm1492_Terminal_View.h"
#include "../asm1492_Library.h"
#include "../asm1492_Customer.h"
#include "../asm1492_Librarian.h"
#include "../asm1492_Transaction.h"
#include "../asm1492_Transaction_Item.h"
#include "../media/asm1492_Media.h"
#include "../media/asm1492_Book.h"
#include "../media/asm1492_Movie.h"
#include "../media/asm1492_Music_Album.h"
#include "../media/asm1492_Television_Show_Season.h"
#include "../media/asm1492_Video_Game.h"

bool Exit_Function::operator()() {
	controller->get_view()->exit();
	return false;
}

bool Add_Media_Function::operator()() {
	Media::Format format = Media::string_to_format(controller->prompt_for_string("Media Format (Unspecified, Book, Movie, Music Album, Television Show Season, Video Game)"));
	string title = controller->prompt_for_string("Media Title");
	string genre = controller->prompt_for_string("Media Genre");

	switch(format) {
		case Media::Format::Unspecified:
			controller->get_library()->create_new_media(format, title, genre);
			break;
		case Media::Format::Book: {
			string author = controller->prompt_for_string("Author");
			int copyright = controller->prompt_for_int("Copyright Date");
			int pages = controller->prompt_for_int("Page Count");
			controller->get_library()->create_new_media(new Book(title, genre, author, copyright, pages));
			break;
		}
		case Media::Format::Movie: {
			string producer = controller->prompt_for_string("Producer");
			string director = controller->prompt_for_string("Director");
			int release = controller->prompt_for_int("Release Year");
			vector<string> leads = controller->prompt_for_string_list("Leading Actors (Please enter all actor's names separated by commas)");
			double runtime = controller->prompt_for_double("Runtime (minutes)");
			controller->get_library()->create_new_media(new Movie(title, genre, producer, director, release, leads, runtime));
			break;
		}
		case Media::Format::Music_Album: {
			int release = controller->prompt_for_int("Release Year");
			string artist = controller->prompt_for_string("Artist");
			vector<string> tracks = controller->prompt_for_string_list("Album Tracks (Please enter all track names seperated by commas)");
			controller->get_library()->create_new_media(new Music_Album(title, genre, release, artist, tracks));
			break;
		}
		case Media::Format::Television_Show_Season: {
			string producer = controller->prompt_for_string("Producer");
			vector<string> directors = controller->prompt_for_string_list("Directors (Please enter all director's names seperated by commas)");
			vector<string> leads = controller->prompt_for_string_list("Leading Actors (Please enter all actor's names separated by commas)");
			double runtime = controller->prompt_for_double("Runtime (minutes)");
			int season = controller->prompt_for_int("Season Number");
			int release = controller->prompt_for_int("Release Year");			
			controller->get_library()->create_new_media(new Television_Show_Season(title, genre, producer, directors, leads, runtime, season, release));
			break;
		}
		case Media::Format::Video_Game: {
			int release = controller->prompt_for_int("Release Year");
			string studio = controller->prompt_for_string("Studio");
			controller->get_library()->create_new_media(new Video_Game(title, genre, release, studio));
			break;
		}
	}

	return true;
}

bool Add_Bundle_Function::operator()() {
	string name = controller->prompt_for_string("Bundle Name");
	vector<int> medias = controller->prompt_for_int_list("Media ID Numbers (Please enter all ID numbers seperated by a space)");
	controller->get_library()->create_new_bundle(name, medias);
	return true;
}

bool Delete_Media_Function::operator()() {
	int media = controller->prompt_for_int("Media ID Number to delete");
	controller->get_library()->delete_media(media);
	return true;
}

bool Delete_Bundle_Function::operator()() {
	string name = controller->prompt_for_string("Bundle name to delete");
	controller->get_library()->delete_bundle(name);
	return true;
}

bool Check_Out_Function::operator()() {
	Customer* customer = Library::get_customer(controller->prompt_for_int("7-Digit Customer ID Number"));
	vector<Media*> medias = Library::to_media_list(controller->prompt_for_int_list("Media ID Numbers to check out (Please enter all ID numbers seperated by a space)"));
	vector<Bundle*> bundles = Library::to_bundle_list(controller->prompt_for_string_list("Bundle Names to check out (Please enter all Bundle Names seperated by commas)"));
	Date check_out_date = controller->prompt_for_date("Transaction Check-Out");
	Transaction* trans = ((Librarian_Controller*) controller)->get_librarian()->check_out(customer, medias, bundles, check_out_date);
	controller->get_view()->print_transaction(trans);
	return true;
}

bool Check_In_Function::operator()() {
	Customer* customer = Library::get_customer(controller->prompt_for_int("7-Digit Customer ID Number"));
	vector<Media*> medias = Library::to_media_list(controller->prompt_for_int_list("Media ID Numbers to check in (Please enter all ID numbers seperated by a space)"));
	vector<Bundle*> bundles = Library::to_bundle_list(controller->prompt_for_string_list("Bundle Names to check in (Please enter all Bundle Names seperated by commas)"));
	Date check_in_date = controller->prompt_for_date("Transaction Check-In");
	((Librarian_Controller*) controller)->get_librarian()->check_in(customer, medias, bundles, check_in_date);
	return true;
}

bool Print_Info_Function::operator()() {
	if(type == "Customer")
		controller->get_view()->print_customer(((Customer_Controller*) controller)->get_customer());
	else if(type == "Librarian")
		controller->get_view()->print_librarian(((Librarian_Controller*) controller)->get_librarian());
	return true;
}

bool Print_Items_Function::operator()() {
	controller->get_view()->print_items(((Customer_Controller*) controller)->get_customer()->get_checked_out_items());
	return true;
}

bool Pay_Balance_Function::operator()() {
	((Customer_Controller*) controller)->get_customer()->pay_balance();
	controller->get_view()->pay_balance();
	return true;
}

bool Print_Catalog_Function::operator()() {
	controller->get_view()->print_catalog();
	return true;
}

bool Login_Function::operator()() {
	if(name == "Administrator") {
		Admin_Controller* control = new Admin_Controller(controller->get_library(), controller->get_view());
		control->run_cli();
	} else if(name == "Librarian") {
		Librarian_Login_Controller* control = new Librarian_Login_Controller(controller->get_library(), controller->get_view());
		control->run_cli();
	} else if(name == "Customer") {
		Customer_Login_Controller* control = new Customer_Login_Controller(controller->get_library(), controller->get_view());
		control->run_cli();
	}
	return true;
}

bool Librarian_Login_Function::operator()() {
	if(name == "New Librarian") {
		string name = controller->prompt_for_string("Full Name");
		librarian = controller->get_library()->create_new_librarian(name);
	}
	Librarian_Controller* control = new Librarian_Controller(controller->get_library(), controller->get_view(), librarian);
	control->run_cli();

	return false;
}

bool Customer_Login_Function::operator()() {
	if(name == "New Customer") {
		string name = controller->prompt_for_string("Full Name");
		long phone = controller->prompt_for_long("Phone Number");
		string email = controller->prompt_for_string("Email Address");
		customer = controller->get_library()->create_new_customer(name, phone, email);
	}
	Customer_Controller* control = new Customer_Controller(controller->get_library(), controller->get_view(), customer);
	control->run_cli();

	return false;
}

bool Logout_Function::operator()() {
	return false;
}

bool Load_Function::operator()() {
	if(!controller->get_library()->load("librario_save.json"))
		controller->get_view()->load_fail();
	else
		controller->get_view()->load();
	return true;
}

bool Save_Function::operator()() {
	controller->get_library()->save("librario_save.json");
	controller->get_view()->save();
	return true;
}