#include "asm1492_Gui_Handler.h"

#include "asm1492_Main_Window.h"

bool Gui_Handler::run_terminal = true;

void Gui_Handler::start_gui(int argc, char* argv[]) {
	auto app = Gtk::Application::create(argc, argv, "com.virtualoso.librario");
	Main_Window window;
	window.set_default_size(450, 150);
	window.set_icon_name("accessories-dictionary");
	app->run(window);

	run_terminal = false;
}