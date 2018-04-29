#pragma once

#include <gtkmm.h>

#include "../asm1492_Librarian.h"
#include "../asm1492_Customer.h"

class Main_Window;

class User_Window : public Gtk::Box {
public:
	User_Window(Main_Window& parent_, User* user_);
	virtual void set_inactive();

protected:
	Main_Window& parent;
	User* user;
};

class Administrator_Window : public User_Window {
public:
	Administrator_Window(Main_Window& parent_, User* admin);
	void set_inactive();
};

class Librarian_Window : public User_Window {
public:
	Librarian_Window(Main_Window& parent_, User* librarian);
	void set_inactive();
};

class Customer_Window : public User_Window {
public:
	Customer_Window(Main_Window& parent_, User* customer);
	void set_inactive();
};