#pragma once

#include <gtkmm.h>

#include "asm1492_Input_Frame.h"

class Media;

class Add_Media_Dialog : public Gtk::Dialog {
public:
	Add_Media_Dialog(Gtk::Window& parent);
	virtual ~Add_Media_Dialog() {};
	Media* create_media();
	
private:

	class Input_Group {
	public:
		void add_entry(Input_Frame* entry, Gtk::Box* parent) {
			add_entry(entry);
			parent->pack_start(*entry);
		}
		void add_entry(Input_Frame* entry) {
			entries.push_back(entry);
		}
		void clear_and_show() {
			for(Input_Frame* entry : entries)
				entry->clear_and_show();
		}
		void hide() {
			for(Input_Frame* entry : entries)
				entry->hide();
		}
	private:
		vector<Input_Frame*> entries;
	};

	void format_changed();

	Input_Group book;
	Input_Group movie;
	Input_Group music_album;
	Input_Group television_show_season;
	Input_Group video_game;

	Gtk::ComboBoxText format;
	Clearable_Entry title;
	Clearable_Entry genre;
	Clearable_Entry author;
	Clearable_Entry copyright;
	Clearable_Entry pages;
	Clearable_Entry producer;
	Clearable_Entry director;
	Clearable_Entry release;
	Clearable_Entry runtime;
	List_Entry leads;
	Clearable_Entry artist;
	List_Entry tracks;
	List_Entry directors;
	Clearable_Entry season;
	Clearable_Entry studio;
};