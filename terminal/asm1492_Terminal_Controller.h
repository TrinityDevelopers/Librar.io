#pragma once

#include <vector>
#include <string>

using namespace std;

class Terminal_View;
class Library;
class Menu_Function;
class Customer;
class Librarian;
class Date;

class Terminal_Controller {
public:
	Terminal_Controller(Library* lib, Terminal_View* view_) : library(lib), view(view_) {};

	virtual void init();
	void run_cli();
	void read_cmd(int* cmd);
	bool execute_cmd(int cmd);

	string prompt_for_string(string arg);
	int prompt_for_int(string arg);
	long prompt_for_long(string arg);
	double prompt_for_double(string arg);
	vector<string> prompt_for_string_list(string arg);
	vector<int> prompt_for_int_list(string arg);
	Date prompt_for_date(string arg);

	Library* get_library() { return library; };
	Terminal_View* get_view() { return view; };

protected:
	vector<Menu_Function*> functions;
	Library* library;
	Terminal_View* view;
};

class Librarian_Login_Controller : public Terminal_Controller {
public:
	Librarian_Login_Controller(Library* lib, Terminal_View* view_) : Terminal_Controller(lib, view_) {};
	
	virtual void init();
};

class Customer_Login_Controller : public Terminal_Controller {
public:
	Customer_Login_Controller(Library* lib, Terminal_View* view_) : Terminal_Controller(lib, view_) {};
	
	virtual void init();
};

class Admin_Controller : public Terminal_Controller {
public:
	Admin_Controller(Library* lib, Terminal_View* view_) : Terminal_Controller(lib, view_) {};
	
	virtual void init();
};

class Librarian_Controller : public Terminal_Controller {
public:
	Librarian_Controller(Library* lib, Terminal_View* view_, Librarian* librarian_) : Terminal_Controller(lib, view_), librarian(librarian_) {};
	
	virtual void init();

	Librarian* get_librarian() { return librarian; };

private:
	Librarian* librarian;
};

class Customer_Controller : public Terminal_Controller {
public:
	Customer_Controller(Library* lib, Terminal_View* view_, Customer* cust) : Terminal_Controller(lib, view_), customer(cust) {};
	
	virtual void init();

	Customer* get_customer() { return customer; };

private:
	Customer* customer;
};