#include <thread>

#include "asm1492_Library.h"
#include "terminal/asm1492_Terminal_View.h"
#include "terminal/asm1492_Terminal_Controller.h"
#include "gui/asm1492_Librario_App.h"

static void run_terminal(int argc, char* argv[]) {
	if(argc > 1 && !string(argv[1]).compare("-t")) {
		Terminal_View* view = new Terminal_View(Library::get_instance());
		Terminal_Controller* control = new Terminal_Controller(Library::get_instance(), view);
		control->run_cli();
	}
}

int main(int argc, char* argv[]) {
	thread t1 (run_terminal, argc, argv);
	int ret = Librario_App::create()->run();
	t1.join();
	return ret;
}