#pragma once

#include <gtkmm.h>

#include "../elements/asm1492_Input_Frame.h"

class Librarian;

class Create_Librarian_Dialog : public Gtk::Dialog {
public:
	Create_Librarian_Dialog(Gtk::Window& parent);
	virtual ~Create_Librarian_Dialog() {};
	Librarian* create_librarian();

private:
	Clearable_Entry name;
};