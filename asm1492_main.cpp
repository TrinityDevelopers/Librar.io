#include <iostream>
#include <thread>

#include "asm1492_Library.h"
#include "terminal/asm1492_Terminal_View.h"
#include "terminal/asm1492_Terminal_Controller.h"
#include "gui/asm1492_Gui_Handler.h"


int main(int argc, char* argv[]) {
	thread t1 (Gui_Handler::start_gui, argc, argv);

	Library* library = Library::get_instance();
	Terminal_View* view = new Terminal_View(library);
	Terminal_Controller* control = new Terminal_Controller(library, view);
	control->run_cli();

	t1.join();

	return 0;
}