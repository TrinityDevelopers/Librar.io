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

class Library {
public:
	Library(int media_id = 1000, int librarian_id = 1000000, int customer_id = 1000000, int transaction_id = 0)
		: current_media_id(media_id), current_librarian_id(librarian_id), current_customer_id(customer_id), current_transaction_id(transaction_id) {};

	Media* create_new_media(Media::Format format, string title, string genre);
	Media* create_new_media(Media* media);
	Media* create_new_media(Json::Value&);
	Bundle* create_new_bundle(string name);
	Bundle* create_new_bundle(string name, vector<Media*> media);
	Bundle* create_new_bundle(string name, vector<int> media);
	Bundle* create_new_bundle(Json::Value&);
	Librarian* create_new_librarian(string name);
	Librarian* create_new_librarian(Json::Value&);
	Customer* create_new_customer(string name, long phone, string email, double balance = 0);
	Customer* create_new_customer(Json::Value&);
	Transaction* create_new_transaction(Date check_out, Librarian* lib, Customer* cust);
	Transaction* create_new_transaction(Json::Value&);

	bool delete_media(int id);
	bool delete_bundle(string name);

	vector<Media*> get_all_medias();
	vector<Bundle*> get_all_bundles();
	vector<Librarian*> get_all_librarians();
	vector<Customer*> get_all_customers();
	vector<Transaction*> get_all_transactions();

	bool load(string file);
	void save(string file);

	static string create_call_num(int id, string title);
	static int create_media_id();
	static Media* get_media(int id);
	static Bundle* get_bundle(string name);
	static Customer* get_customer(int id);
	static Librarian* get_librarian(int id);
	static Transaction* get_transaction(int id);
	static vector<Media*> to_media_list(vector<int> ids);
	static vector<Bundle*> to_bundle_list(vector<string> names);

	static Library* get_instance();

private:
	map<string, Bundle*> bundles;
	map<int, Media*> medias;
	map<int, Librarian*> librarians;
	map<int, Customer*> customers;
	map<int, Transaction*> transactions;
	int current_media_id;
	int current_librarian_id;
	int current_customer_id;
	int current_transaction_id;

	static Library* instance;
};