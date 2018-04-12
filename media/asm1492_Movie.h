#pragma once

#include <vector>

#include "asm1492_Media.h"

class Movie : public Media {
public:
	Movie(string title_, string genre_, string prod = "unknown", string direc = "unknown", int release = -1, vector<string> leads = {}, double time = 0)
		: Media(Format::Movie, title_, genre_), producer(prod), director(direc), release_year(release), leading_actors(leads), runtime(time) {};

	int get_release_year() { return release_year; };
	string get_producer() { return producer; };
	string get_director() { return director; };
	vector<string> get_leading_actors() { return leading_actors; };
	double get_runtime() { return runtime; };
	
	string to_string() const;
	friend ostream& operator<<(ostream& ost, const Movie& movie_two);

	Date get_due_date(Date check_out_date);
	double get_daily_fee();

	void save(Json::Value&);
	void load(Json::Value&);

private:
	int release_year;
	string producer;
	string director;
	vector<string> leading_actors;
	double runtime;
};