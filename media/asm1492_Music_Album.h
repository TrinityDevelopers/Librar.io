#pragma once

#include <vector>

#include "asm1492_Media.h"

class Music_Album : public Media {
public:
	Music_Album(string title_, string genre_, int release = -1, string artist_ = "unknown", vector<string> tracks_ = {})
		: Media(Format::Music_Album, title_, genre_), release_year(release), artist(artist_), tracks(tracks_) {};

	int get_release_year() { return release_year; };
	string get_artist() { return artist; };
	vector<string> get_tracks() { return tracks; };

	string to_string() const;
	friend ostream& operator<<(ostream& ost, const Music_Album& album_two);

private:
	int release_year;
	string artist;
	vector<string> tracks;
};