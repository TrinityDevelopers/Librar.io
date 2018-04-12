#include "asm1492_Library.h"

#include "media/asm1492_Book.h"
#include "media/asm1492_Movie.h"
#include "media/asm1492_Music_Album.h"
#include "media/asm1492_Television_Show_Season.h"
#include "media/asm1492_Video_Game.h"
#include "asm1492_Bundle.h"
#include "asm1492_Librarian.h"
#include "asm1492_Customer.h"
#include "asm1492_Transaction.h"
#include "asm1492_Transaction_Item.h"

#include <sstream>
#include <fstream>

Library* Library::instance;


Media* Library::create_new_media(Media::Format format, string title, string genre) {
	Media* media;
	switch(format) {
		case Media::Format::Unspecified:
			media = new Media(format, title, genre);
			break;
		case Media::Format::Book:
			media = new Book(title, genre);
			break;
		case Media::Format::Movie:
			media = new Movie(title, genre);
			break;
		case Media::Format::Music_Album:
			media = new Music_Album(title, genre);
			break;
		case Media::Format::Television_Show_Season:
			media = new Television_Show_Season(title, genre);
			break;
		case Media::Format::Video_Game:
			media = new Video_Game(title, genre);
			break;
	}
	return create_new_media(media);
}

Media* Library::create_new_media(Media* media) {
	medias[media->get_id_number()] = media;
	return media;
}

Media* Library::create_new_media(Json::Value& media) {
	Media::Format format = Media::string_to_format(media.get("format", "Unspecified").asString());
	string title = media.get("title", "unknown").asString();
	string genre = media.get("genre", "unknown").asString();
	Media* ret = create_new_media(format, title, genre);
	ret->load(media);
	return ret;
}

Bundle* Library::create_new_bundle(string name) {
	return create_new_bundle(name, vector<Media*>{});
}

Bundle* Library::create_new_bundle(string name, vector<Media*> media) {
	Bundle* bundle = new Bundle(name, media);
	bundles[name] = bundle;
	return bundle;
}

Bundle* Library::create_new_bundle(string name, vector<int> media) {
	return create_new_bundle(name, to_media_list(media));
}

Bundle* Library::create_new_bundle(Json::Value& bundle) {
	string name = bundle.get("name", "unknown").asString();
	vector<int> media;
	Json::Value media_list = bundle["medias"];
	for(int i = 0; i < media_list.size(); i++)
		media.push_back(media_list[i].asInt());
	Bundle* ret = create_new_bundle(name, media);
	if(bundle.get("checked_out", false).asBool())
		ret->check_out();
}

Librarian* Library::create_new_librarian(string name) {
	Librarian* librarian = new Librarian(name, current_librarian_id);
	librarians[current_librarian_id] = librarian;
	current_librarian_id++;
	return librarian;
}

Librarian* Library::create_new_librarian(Json::Value& librarian) {
	string name = librarian.get("name", "unknown").asString();
	return create_new_librarian(name);
}

Customer* Library::create_new_customer(string name, long phone, string email, double balance) {
	Customer* customer = new Customer(name, current_customer_id, phone, email, balance);
	customers[current_customer_id] = customer;
	current_customer_id++;
	return customer;
}

Customer* Library::create_new_customer(Json::Value& customer) {
	string name = customer.get("name", "unknown").asString();
	long phone = customer.get("phone", 0000000000).asInt64();
	string email = customer.get("email", "").asString();
	double balance = customer.get("balance", 0).asDouble();
	Customer* cust = create_new_customer(name, phone, email, balance);
	Json::Value items = customer["checked_out_items"];
	for(int i = 0; i < items.size(); i++)
		cust->add_transaction_item(Transaction_Item::load(items[i]));
	return cust;
}

Transaction* Library::create_new_transaction(Date check_out, Librarian* lib, Customer* cust) {
	Transaction* trans = new Transaction(current_transaction_id, check_out, lib, cust);
	transactions[current_transaction_id] = trans;
	current_transaction_id++;
	return trans;
}

Transaction* Library::create_new_transaction(Json::Value& transaction) {
	Date check_out_date = Date::load(transaction["check_out_date"]);
	Librarian* librarian = Library::get_librarian(transaction["librarian"].asInt());
	Customer* customer = Library::get_customer(transaction["customer"].asInt());
	Transaction* ret = create_new_transaction(check_out_date, librarian, customer);
	Json::Value items = transaction["checked_out_items"];
	for(int i = 0; i < items.size(); i++)
		ret->add_transaction_item(Transaction_Item::load(items[i]));
	return ret;
}

bool Library::delete_media(int id) {
	return medias.erase(id);
}

bool Library::delete_bundle(string name) {
	return bundles.erase(name);
}

vector<Media*> Library::get_all_medias() {
	vector<Media*> media_vec;
	for(pair<int, Media*> media : medias)
		media_vec.push_back(media.second);
	return media_vec;
}

vector<Bundle*> Library::get_all_bundles() {
	vector<Bundle*> bundle_vec;
	for(pair<string, Bundle*> it : bundles)
		bundle_vec.push_back(it.second);
	return bundle_vec;
}

vector<Librarian*> Library::get_all_librarians() {
	vector<Librarian*> librarian_vec;
	for(pair<int, Librarian*> it : librarians)
		librarian_vec.push_back(it.second);
	return librarian_vec;
}

vector<Customer*> Library::get_all_customers() {
	vector<Customer*> customer_vec;
	for(pair<int, Customer*> it : customers)
		customer_vec.push_back(it.second);
	return customer_vec;
}

vector<Transaction*> Library::get_all_transactions() {
	vector<Transaction*> transaction_vec;
	for(pair<int, Transaction*> it : transactions)
		transaction_vec.push_back(it.second);
	return transaction_vec;
}

bool Library::load(string file) {
	ifstream load_file (file.c_str());
	Json::Value root;
	Json::Reader reader;
	if(!reader.parse(load_file, root))
		return false;
	Json::Value media_list = root["medias"];
	for(int i = 0; i < media_list.size(); i++)
		create_new_media(media_list[i]);
	Json::Value bundle_list = root["bundles"];
	for(int i = 0; i < bundle_list.size(); i++)
		create_new_bundle(bundle_list[i]);
	Json::Value librarian_list = root["librarians"];
	for(int i = 0; i < librarian_list.size(); i++)
		create_new_librarian(librarian_list[i]);
	Json::Value customer_list = root["customers"];
	for(int i = 0; i < customer_list.size(); i++)
		create_new_customer(customer_list[i]);
	Json::Value transaction_list = root["transactions"];
	for(int i = 0; i < transaction_list.size(); i++)
		create_new_transaction(transaction_list[i]);
	return true;
}

void Library::save(string file) {
	ofstream save_file (file.c_str(), ofstream::trunc);
	Json::Value root;
	for(pair<int, Media*> it : medias) {
		Json::Value media;
		it.second->save(media);
		root["medias"].append(media);
	}
	for(pair<string, Bundle*> it : bundles) {
		Json::Value bundle;
		it.second->save(bundle);
		root["bundles"].append(bundle);
	}
	for(pair<int, Librarian*> it : librarians) {
		Json::Value librarian;
		it.second->save(librarian);
		root["librarians"].append(librarian);
	}
	for(pair<int, Customer*> it : customers) {
		Json::Value customer;
		it.second->save(customer);
		root["customers"].append(customer);
	}
	for(pair<int, Transaction*> it : transactions) {
		Json::Value transaction;
		it.second->save(transaction);
		root["transactions"].append(transaction);
	}
	if(save_file.is_open()) {
		save_file << root;
		save_file.close();
	}
}

string Library::create_call_num(int id, string title) {
	stringstream stm;
	stm << id << "-" << title.substr(0, 4);
	return stm.str();
}

int Library::create_media_id() {
	int ret = get_instance()->current_media_id;
	get_instance()->current_media_id++;
	return ret;
}

Media* Library::get_media(int id) {
	if(get_instance()->medias.count(id))
		return get_instance()->medias.at(id);
	return NULL;
}

Bundle* Library::get_bundle(string name) {
	if(get_instance()->bundles.count(name))
		return get_instance()->bundles.at(name);
	return NULL;
}

Customer* Library::get_customer(int id) {
	if(get_instance()->customers.count(id))
		return get_instance()->customers.at(id);
	return NULL;
}

Librarian* Library::get_librarian(int id) {
	if(get_instance()->librarians.count(id))
		return get_instance()->librarians.at(id);
	return NULL;
}

Transaction* Library::get_transaction(int id) {
	if(get_instance()->transactions.count(id))
		return get_instance()->transactions.at(id);
	return NULL;
}

vector<Media*> Library::to_media_list(vector<int> ids) {
	vector<Media*> media_vec;
	for(int id : ids)
		media_vec.push_back(get_media(id));
	return media_vec;
}

vector<Bundle*> Library::to_bundle_list(vector<string> names) {
	vector<Bundle*> bundle_vec;
	for(string name : names)
		bundle_vec.push_back(get_bundle(name));
	return bundle_vec;
}

Library* Library::get_instance() {
	if(!instance)
		instance = new Library();
	return instance;
}