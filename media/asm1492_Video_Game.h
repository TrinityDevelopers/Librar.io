#pragma once

#include "asm1492_Media.h"

class Video_Game : public Media {
public:
	Video_Game(string title_, string genre_, int release = -1, string studio_ = "unknown")
		: Media(Format::Video_Game, title_, genre_), release_year(release), studio(studio_) {};

	int get_release_year() { return release_year; };
	string get_studio() { return studio; };

	string to_string() const;
	friend ostream& operator<<(ostream& ost, const Video_Game& game_two);

	double get_daily_fee();

private:
	int release_year;
	string studio;
};