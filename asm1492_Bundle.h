#pragma once

#include <set>
#include <vector>
#include <sstream>

#include "json/asm1492_json.h"
#include "media/asm1492_Media.h"

class Bundle {
public:
	Bundle(string name_, vector<Media*> medias_ = {});

	bool add(Media* media);
	bool add(int id);
	bool remove(Media* media);
	bool remove(int id);

	void check_out();
	void check_in();
	void set_checked_out();
	void set_checked_in();
	bool is_checked_out() { return checked_out; };

	string get_name() { return name; };
	set<Media*> get_medias() { return medias; };
	int get_media_count() { return medias.size(); };
	string get_medias_string();

	string to_compact_string();

	friend ostream& operator<<(ostream& ost, const Bundle& bundle_two);

	void save(Json::Value&);

private:
	string name;
	set<Media*> medias;
	bool checked_out;
};