#pragma once

#include <gtkmm.h>

class Gui_Handler {
public:
	static void start_gui(int argc, char* argv[]);

	static bool run_terminal;
};