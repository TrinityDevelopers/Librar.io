#pragma once

#include <gtkmm.h>

#include "../elements/asm1492_Input_Frame.h"
#include "../elements/asm1492_Browse_Window.h"

class Bundle;

class Add_Bundle_Dialog : public Gtk::Dialog {
public:
	Add_Bundle_Dialog(Gtk::Window& parent);
	virtual ~Add_Bundle_Dialog() {};
	Bundle* create_bundle();

private:
	Clearable_Entry name;
	Browse_Window medias;
};