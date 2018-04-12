#include "asm1492_Media.h"
#include "../asm1492_Bundle.h"
#include "../asm1492_Library.h"
#include "../asm1492_Date.h"

Media::Media(Format form, string title_, string genre_)
	: format(form), title(title_), genre(genre_), contained_bundle(NULL), in_bundle(false), checked_out(false) {

	id_number = Library::create_media_id();
	call_number = Library::create_call_num(id_number, title_);
}

void Media::check_out() {
	if(!checked_out) {
		checked_out = true;
		if(in_bundle)
			contained_bundle->set_checked_out();
	}
}

void Media::check_in() {
	if(checked_out) {
		checked_out = false;
		if(in_bundle)
			contained_bundle->set_checked_in();
	}
}

bool Media::is_checked_out() {
	return checked_out;
}

void Media::add_to_bundle(Bundle* bundle) {
	contained_bundle = bundle;
	in_bundle = true;
}

void Media::remove_from_bundle() {
	contained_bundle = NULL;
	in_bundle = false;
}

bool Media::is_in_bundle() {
	return in_bundle;
}

string Media::to_compact_string() const {
	stringstream stm;
	stm << "Format: " << setw(22) << left << format_to_string(format);
	stm << "   ID Number: " << id_number;
	stm << "   Title: " << title;
	return stm.str();
}

string Media::to_string() const {
	stringstream stm;
	stm << setw(18) << left << "Format: " << Media::format_to_string(format) << endl;
	stm << setw(18) << left << "ID Number: " << id_number << endl;
	stm << setw(18) << left << "Call Number: " << call_number << endl;
	stm << setw(18) << left << "Checkout status: " << (checked_out ? "Checked Out" : "Checked In") << endl;
	if(in_bundle)
		stm << setw(18) << left << "Associate Bundle: " << contained_bundle->get_name() << endl;
	stm << setw(18) << left << "Title: " << title << endl;
	stm << setw(18) << left << "Genre: " << genre << endl;
	return stm.str();
}

ostream& operator<<(ostream& ost, const Media& media_two) {
	ost << media_two.to_string();
	return ost;
}

Date Media::get_due_date(Date check_out_date) {
	check_out_date.add_days(21);
	return check_out_date;
}

double Media::get_daily_fee() {
	return 0.25;
}

void Media::save(Json::Value& media) {
	media["checked_out"] = checked_out;
	media["format"] = format_to_string(format);
	media["title"] = title;
	media["genre"] = genre;
}

void Media::load(Json::Value& media) {
	checked_out = media.get("checked_out", false).asBool();
}

string Media::format_to_string(Format format) {
	switch(format) {
		case Format::Unspecified:
			return "Unspecified";
			break;
		case Format::Book:
			return "Book";
			break;
		case Format::Movie:
			return "Movie";
			break;
		case Format::Video_Game:
			return "Video Game";
			break;
		case Format::Music_Album:
			return "Music Album";
			break;
		case Format::Television_Show_Season:
			return "Television Show Season";
			break;
		default:
			return "Unknown";
			break;
	}
}

Media::Format Media::string_to_format(string format) {
	if(format == "Book")
		return Format::Book;
	else if(format == "Movie")
		return Format::Movie;
	else if(format == "Video Game")
		return Format::Video_Game;
	else if(format == "Music Album")
		return Format::Music_Album;
	else if(format == "Television Show Season")
		return Format::Television_Show_Season;
	else
		return Format::Unspecified;
}