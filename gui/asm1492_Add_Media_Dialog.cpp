#include "asm1492_Add_Media_Dialog.h"

#include "../media/asm1492_Media.h"

Add_Media_Dialog::Add_Media_Dialog(Gtk::Window& parent) 
	: Gtk::Dialog("Add Media", parent), leads("Actor Name"), tracks("Track Name"), directors("Director Name") {
	
	set_resizable(false);

	for(int format = 0; format < 6; format++)
		media_format.append(Media::format_to_string((Media::Format)format));
	media_format.set_active(0);

	Input_Frame* frame = new Input_Frame("Media Format", &media_format);
	get_content_area()->pack_start(*frame);
	
	media_format.signal_changed().connect(sigc::mem_fun(*this, &Add_Media_Dialog::media_format_changed));
	frame->show_all();

	title.set_placeholder_text("Title");
	frame = new Input_Frame("Media Title", &title);
	get_content_area()->pack_start(*frame);
	frame->show_all();

	genre.set_placeholder_text("Genre");
	frame = new Input_Frame("Media Genre", &genre);
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
	Input_Frame* producer_frame = new Input_Frame("Producer", &producer);
	Input_Frame* release_frame = new Input_Frame("Release Year", &release);
	Input_Frame* runtime_frame = new Input_Frame("Runtime (minutes)", &runtime);
	Input_Frame* leads_frame = new Input_Frame("Leading Actors", &leads);

	book.add_entry(new Input_Frame("Author", &author), get_content_area());
	book.add_entry(new Input_Frame("Copyright Date", &copyright), get_content_area());
	book.add_entry(new Input_Frame("Page Count", &pages), get_content_area());

	movie.add_entry(producer_frame, get_content_area());
	movie.add_entry(new Input_Frame("Director", &director), get_content_area());
	movie.add_entry(release_frame, get_content_area());
	movie.add_entry(runtime_frame, get_content_area());
	movie.add_entry(leads_frame, get_content_area());

	music_album.add_entry(new Input_Frame("Artist", &artist), get_content_area());
	music_album.add_entry(new Input_Frame("Album Tracks", &tracks), get_content_area());

	television_show_season.add_entry(producer_frame);
	television_show_season.add_entry(runtime_frame);
	television_show_season.add_entry(new Input_Frame("Season Number", &season), get_content_area());
	television_show_season.add_entry(release_frame);
	television_show_season.add_entry(new Input_Frame("Directors", &directors), get_content_area());
	television_show_season.add_entry(leads_frame);

	video_game.add_entry(release_frame);
	video_game.add_entry(new Input_Frame("Studio", &studio), get_content_area());

	media_format_changed();

	add_button("_Cancel", 0);
	add_button("_OK", 1);

	get_action_area()->set_layout(Gtk::BUTTONBOX_EXPAND);
}

void Add_Media_Dialog::media_format_changed() {
	book.hide();
	movie.hide();
	music_album.hide();
	television_show_season.hide();
	video_game.hide();
	switch((Media::Format) media_format.get_active_row_number()) {
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
		default:
			break;
	}
}