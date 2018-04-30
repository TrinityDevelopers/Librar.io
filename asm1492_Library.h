#pragma once

#include <map>
#include <vector>

#include "json/asm1492_json.h"
#include "media/asm1492_Media.h"
#include "asm1492_Date.h"

using namespace std;

class Bundle;
class Librarian;
class Customer;
class Transaction;
class User;

class Library {
public:
	Library(int media_id = MEDIA_ID_LOW, int librarian_id = LIBRARIAN_ID_LOW, int customer_id = CUSTOMER_ID_LOW, int transaction_id = TRANSACTION_ID_LOW)
		: current_media_id(media_id), current_librarian_id(librarian_id), current_customer_id(customer_id), current_transaction_id(transaction_id), name("Library"), saved(true) {};

	Media* create_new_media(Media::Format format, string title, string genre);
	Media* create_new_media(Media* media);
	Media* create_new_media(Json::Value&);
	Bundle* create_new_bundle(string name);
	Bundle* create_new_bundle(string name, vector<Media*> media);
	Bundle* create_new_bundle(string name, vector<int> media);
	Bundle* create_new_bundle(Json::Value&);
	User* create_administrator(string name, string p_hex = "");
	User* create_administrator(Json::Value&);
	Librarian* create_new_librarian(string name, string p_hex = "");
	Librarian* create_new_librarian(Json::Value&);
	Customer* create_new_customer(string name, long phone, string email, string p_hex = "", double balance = 0);
	Customer* create_new_customer(Json::Value&);
	Transaction* create_new_transaction(Date check_out, Librarian* lib, Customer* cust);
	Transaction* create_new_transaction(Json::Value&);

	bool delete_media(int id);
	bool delete_bundle(string name);

	vector<Media*> get_all_medias();
	vector<Bundle*> get_all_bundles();
	vector<User*> get_all_users();
	vector<Librarian*> get_all_librarians();
	vector<Customer*> get_all_customers();
	vector<Transaction*> get_all_transactions();

	Customer* get_owner(Media* media);
	Customer* get_owner(Bundle* bundle);

	bool load(string file);
	void save(string file);

	string get_name() { return name; };
	void set_name(string name_) { name = name_; };
	string get_path() { return file_path; };
	void set_path(string path) { file_path = path; };
	bool has_file_path() { return !file_path.empty(); };
	bool is_saved() { return saved; };

	int get_current_librarian_id() { return current_librarian_id; };
	int get_current_customer_id() { return current_customer_id; };

	static string create_call_num(int id, string title);
	static int create_media_id();
	static Media* get_media(int id);
	static Bundle* get_bundle(string name);
	static User* get_user(int id);
	static Customer* get_customer(int id);
	static Librarian* get_librarian(int id);
	static Transaction* get_transaction(int id);
	static vector<Media*> to_media_list(vector<int> ids);
	static vector<Bundle*> to_bundle_list(vector<string> names);

	static Library* get_instance();
	static void delete_library();

	static const int MEDIA_ID_LOW;
	static const int LIBRARIAN_ID_LOW;
	static const int CUSTOMER_ID_LOW;
	static const int TRANSACTION_ID_LOW;

private:
	string name;
	string file_path;
	bool saved;
	User* administrator;
	map<string, Bundle*> bundles;
	map<int, Media*> medias;
	map<int, User*> users;
	map<int, Librarian*> librarians;
	map<int, Customer*> customers;
	map<int, Transaction*> transactions;
	int current_media_id;
	int current_librarian_id;
	int current_customer_id;
	int current_transaction_id;

	static Library* instance;
};