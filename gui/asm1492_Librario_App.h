#pragma once

#include <gtkmm.h>

class Main_Window;

class Librario_App : public Gtk::Application {
protected:
	Librario_App();
	void on_activate() override;
	void on_startup() override;

public:
	static Glib::RefPtr<Librario_App> create();

private:
	void create_window();

	void on_window_hide(Main_Window* window);
	void on_action_something();
	void on_action_quit();
};