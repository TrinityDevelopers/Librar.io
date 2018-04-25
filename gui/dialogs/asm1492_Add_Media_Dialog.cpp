#include "asm1492_Add_Media_Dialog.h"

#include "../../media/asm1492_Media.h"
#include "../../media/asm1492_Book.h"
#include "../../media/asm1492_Movie.h"
#include "../../media/asm1492_Music_Album.h"
#include "../../media/asm1492_Television_Show_Season.h"
#include "../../media/asm1492_Video_Game.h"
#include "../../asm1492_Library.h"

Add_Media_Dialog::Add_Media_Dialog(Gtk::Window& parent) 
	: Gtk::Dialog("Add Media", parent), leads("Actor Name"), tracks("Track Name"), directors("Director Name") {
	
	set_resizable(false);

	for(int form = 0; form < 6; form++)
		format.append(Media::format_to_string((Media::Format)form));
	format.set_active(0);

	Input_Frame* frame = Gtk::manage(new Input_Frame("Media Format", &format));
	get_content_area()->pack_start(*frame);
	
	format.signal_changed().connect(sigc::mem_fun(*this, &Add_Media_Dialog::format_changed));
	frame->show_all();

	title.set_placeholder_text("Title");
	frame = Gtk::manage(new Input_Frame("Media Title", &title));
	get_content_area()->pack_start(*frame);
	frame->show_all();

	genre.set_placeholder_text("Genre");
	frame = Gtk::manage(new Input_Frame("Media Genre", &genre));
	get_content_area()->pack_start(*frame);
	frame->show_all();

	author.set_placeholder_text("Author");
	copyright.set_placeholder_text("Copyright");
	pages.set_placeholder_text("Pages");
	producer.set_placeholder_text("Producer");
	director.set_placeholder_text("Director");
	release.set_placeholder_text("Release");
	runtime.set_placeholder_text("Runtime");
	artist.set_placeholder_text("Artist");
	season.set_placeholder_text("Season");
	studio.set_placeholder_text("Studio");
	Input_Frame* producer_frame = Gtk::manage(new Input_Frame("Producer", &producer));
	Input_Frame* release_frame = Gtk::manage(new Input_Frame("Release Year", &release));
	Input_Frame* runtime_frame = Gtk::manage(new Input_Frame("Runtime (minutes)", &runtime));
	Input_Frame* leads_frame = Gtk::manage(new Input_Frame("Leading Actors", &leads));

	book.add_entry(Gtk::manage(new Input_Frame("Author", &author)), get_content_area());
	book.add_entry(Gtk::manage(new Input_Frame("Copyright Date", &copyright)), get_content_area());
	book.add_entry(Gtk::manage(new Input_Frame("Page Count", &pages)), get_content_area());

	movie.add_entry(producer_frame, get_content_area());
	movie.add_entry(Gtk::manage(new Input_Frame("Director", &director)), get_content_area());
	movie.add_entry(release_frame, get_content_area());
	movie.add_entry(runtime_frame, get_content_area());
	movie.add_entry(leads_frame, get_content_area());

	music_album.add_entry(release_frame);
	music_album.add_entry(Gtk::manage(new Input_Frame("Artist", &artist)), get_content_area());
	music_album.add_entry(Gtk::manage(new Input_Frame("Album Tracks", &tracks)), get_content_area());

	television_show_season.add_entry(producer_frame);
	television_show_season.add_entry(runtime_frame);
	television_show_season.add_entry(Gtk::manage(new Input_Frame("Season Number", &season)), get_content_area());
	television_show_season.add_entry(release_frame);
	television_show_season.add_entry(Gtk::manage(new Input_Frame("Directors", &directors)), get_content_area());
	television_show_season.add_entry(leads_frame);

	video_game.add_entry(release_frame);
	video_game.add_entry(Gtk::manage(new Input_Frame("Studio", &studio)), get_content_area());

	format_changed();

	add_button("_Cancel", 0);
	add_button("_OK", 1);

	get_action_area()->set_layout(Gtk::BUTTONBOX_EXPAND);
}

void Add_Media_Dialog::format_changed() {
	book.hide();
	movie.hide();
	music_album.hide();
	television_show_season.hide();
	video_game.hide();
	switch((Media::Format) format.get_active_row_number()) {
		case Media::Format::Unspecified:
			break;
		case Media::Format::Book: {
			book.clear_and_show();
			break;
		}
		case Media::Format::Movie: {
			movie.clear_and_show();
			break;
		}
		case Media::Format::Music_Album: {
			music_album.clear_and_show();
			break;
		}
		case Media::Format::Television_Show_Season: {
			television_show_season.clear_and_show();
			break;
		}
		case Media::Format::Video_Game: {
			video_game.clear_and_show();
			break;
		}
	}
}

Media* Add_Media_Dialog::create_media() {
	Media* media;
	Media::Format media_format = (Media::Format) format.get_active_row_number();
	string media_title = title.get_text();
	string media_genre = genre.get_text();

	switch(media_format) {
		case Media::Format::Unspecified: {
			media = Library::get_instance()->create_new_media(media_format, media_title, media_genre);
			break;
		}
		case Media::Format::Book: {
			media = Library::get_instance()->create_new_media(new Book(media_title, media_genre, author.get_text(), copyright.get_int(), pages.get_int()));
			break;
		}
		case Media::Format::Movie: {
			media = Library::get_instance()->create_new_media(new Movie(media_title, media_genre, producer.get_text(), director.get_text(), release.get_int(), leads.get_string_list(), runtime.get_double()));
			break;
		}
		case Media::Format::Music_Album: {
			media = Library::get_instance()->create_new_media(new Music_Album(media_title, media_genre, release.get_int(), artist.get_text(), tracks.get_string_list()));
			break;
		}
		case Media::Format::Television_Show_Season: {
			media = Library::get_instance()->create_new_media(new Television_Show_Season(media_title, media_genre, producer.get_text(), directors.get_string_list(), leads.get_string_list(), runtime.get_double(), season.get_int(), release.get_int()));
			break;
		}
		case Media::Format::Video_Game: {
			media = Library::get_instance()->create_new_media(new Video_Game(media_title, media_genre, release.get_int(), studio.get_text()));
			break;
		}
	}
	return media;
}