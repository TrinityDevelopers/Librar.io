#pragma once

#include <string>
#include <iomanip>
#include <sstream>
#include <map>

#include "../json/asm1492_json.h"

class Bundle;
class Date;

using namespace std;

class Media {
public:
	enum class Format : unsigned char {
		Unspecified,
		Book,
		Movie,
		Music_Album,
		Television_Show_Season,
		Video_Game
	};

	Media(Format form, string title_, string genre_);
		
	void check_out();
	void check_in();
	bool is_checked_out();

	void add_to_bundle(Bundle* bundle);
	void remove_from_bundle();
	bool is_in_bundle();

	Format get_format() { return format; };
	int get_id_number() { return id_number; };
	string get_call_number() { return call_number; };
	string get_title() { return title; };
	string get_genre() { return genre; };
	Bundle* get_bundle() { return contained_bundle; };

	string to_compact_string() const;
	virtual string to_string() const;
	friend ostream& operator<<(ostream& ost, const Media& media_two);

	virtual Date get_due_date(Date check_out_date);
	virtual double get_daily_fee();

	virtual void save(Json::Value&);
	virtual void load(Json::Value&);

	static string format_to_string(Format format);
	static Format string_to_format(string format);

protected:
	Format format;
	int id_number;
	string call_number;
	string title;
	string genre;
private:
	Bundle* contained_bundle;
	bool in_bundle;
	bool checked_out;
};