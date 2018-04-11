#include <iostream>

#include "asm1492_Library.h"
#include "terminal/asm1492_Terminal_View.h"
#include "terminal/asm1492_Terminal_Controller.h"

int main() {
	Library* library = Library::get_instance();
	Terminal_View* view = new Terminal_View(library);
	Terminal_Controller* control = new Terminal_Controller(library, view);
	control->run_cli();

	return 0;
}