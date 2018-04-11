#pragma once

#include <string>

using namespace std;

class Library;
class Terminal_Controller;
class Librarian;
class Customer;

class Menu_Function {
public:
	Menu_Function(Terminal_Controller* control) : controller(control) {};
	virtual string get_name() = 0;
	virtual bool operator()() = 0;
protected:
	Terminal_Controller* controller;
};

class Login_Function : public Menu_Function {
public:
	Login_Function(Terminal_Controller* control, string name_) : Menu_Function(control), name(name_) {};
	virtual string get_name() { return "Login as " + name; };
	virtual bool operator()();
protected:
	string name;
};

class Librarian_Login_Function : public Login_Function {
public:
	Librarian_Login_Function(Terminal_Controller* control, string name_, Librarian* lib = NULL) : Login_Function(control, name_), librarian(lib) {};
	bool operator()();
private:
	Librarian* librarian;
};

class Customer_Login_Function : public Login_Function {
public:
	Customer_Login_Function(Terminal_Controller* control, string name_, Customer* cust = NULL) : Login_Function(control, name_), customer(cust) {};
	bool operator()();
private:
	Customer* customer;
};

class Logout_Function : public Menu_Function {
public:
	Logout_Function(Terminal_Controller* control) : Menu_Function(control) {};
	string get_name() { return "Logout"; };
	bool operator()();
};

class Exit_Function : public Menu_Function {
public:
	Exit_Function(Terminal_Controller* control) : Menu_Function(control) {};
	string get_name() { return "Exit"; };
	bool operator()();
};

class Add_Media_Function : public Menu_Function {
public:
	Add_Media_Function(Terminal_Controller* control) : Menu_Function(control) {};
	string get_name() { return "Add Media"; };
	bool operator()();
};

class Add_Bundle_Function : public Menu_Function {
public:
	Add_Bundle_Function(Terminal_Controller* control) : Menu_Function(control) {};
	string get_name() { return "Add Bundle"; };
	bool operator()();
};

class Delete_Media_Function : public Menu_Function {
public:
	Delete_Media_Function(Terminal_Controller* control) : Menu_Function(control) {};
	string get_name() { return "Delete Media"; };
	bool operator()();
};

class Delete_Bundle_Function : public Menu_Function {
public:
	Delete_Bundle_Function(Terminal_Controller* control) : Menu_Function(control) {};
	string get_name() { return "Delete Bundle"; };
	bool operator()();
};

class Check_Out_Function : public Menu_Function {
public:
	Check_Out_Function(Terminal_Controller* control) : Menu_Function(control) {};
	string get_name() { return "Check Out"; };
	bool operator()();
};

class Check_In_Function : public Menu_Function {
public:
	Check_In_Function(Terminal_Controller* control) : Menu_Function(control) {};
	string get_name() { return "Check In"; };
	bool operator()();
};

class Print_Info_Function : public Menu_Function {
public:
	Print_Info_Function(Terminal_Controller* control, string type_) : Menu_Function(control), type(type_) {};
	virtual string get_name() { return "Print " + type + " Info"; };
	virtual bool operator()();
private:
	string type;
};

class Print_Items_Function : public Menu_Function {
public:
	Print_Items_Function(Terminal_Controller* control) : Menu_Function(control) {};
	string get_name() { return "Print Checked Out Items"; };
	bool operator()();
};

class Pay_Balance_Function : public Menu_Function {
public:
	Pay_Balance_Function(Terminal_Controller* control) : Menu_Function(control) {};
	string get_name() { return "Pay Balance"; };
	bool operator()();
};

class Print_Catalog_Function : public Menu_Function {
public:
	Print_Catalog_Function(Terminal_Controller* control) : Menu_Function(control) {};
	string get_name() { return "Print Catalog"; };
	bool operator()();
};
