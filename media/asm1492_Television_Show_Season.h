#pragma once

#include <vector>

#include "asm1492_Media.h"

class Television_Show_Season : public Media {
public:
	Television_Show_Season(string title_, string genre_, string prod = "unknown", vector<string> direcs = {}, vector<string> leads = {}, double time = 0, int season = 0, int release = 0)
		: Media(Format::Television_Show_Season, title_, genre_), producer(prod), directors(direcs), leading_actors(leads), runtime(time), season_number(season), release_year(release) {};

	int get_release_year() { return release_year; };
	string get_producer() { return producer; };
	vector<string> get_directors() { return directors; };
	vector<string> get_leading_actors() { return leading_actors; };
	double get_runtime() { return runtime; };
	int get_season_number() { return season_number; };

	string to_string() const;
	friend ostream& operator<<(ostream& ost, const Television_Show_Season& show_two);

	Date get_due_date(Date check_out_date);
	double get_daily_fee();
	
private:
	int release_year;
	string producer;
	vector<string> directors;
	vector<string> leading_actors;
	double runtime;
	int season_number;
};