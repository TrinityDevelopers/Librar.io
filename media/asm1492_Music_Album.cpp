#include "asm1492_Music_Album.h"

string Music_Album::to_string() const {
	stringstream stm;
	stm << Media::to_string();
	stm << setw(18) << left << "Release Year: " << release_year << endl;
	stm << setw(18) << left << "Artist: " << artist << endl;
	stm << setw(18) << left << "Tracks: ";
	for(auto it = tracks.begin(); it != tracks.end(); it++) {
		if(it != tracks.begin()) stm << ", ";
		stm << *it;
	}
	stm << endl;
	return stm.str();
}

ostream& operator<<(ostream& ost, const Music_Album& album_two) {
	ost << album_two.to_string();
	return ost;
}

void Music_Album::save(Json::Value& album) {
	Media::save(album);
	album["release_year"] = release_year;
	album["artist"] = artist;
	Json::Value track_list;
	for(string track : tracks)
		track_list.append(track);
	album["tracks"] = track_list;
}

void Music_Album::load(Json::Value& album) {
	Media::load(album);
	release_year = album.get("release_year", -1).asInt();
	artist = album.get("artist", "unknown").asString();
	Json::Value track_list = album["tracks"];
	for(int i = 0; i < track_list.size(); i++)
		tracks.push_back(track_list[i].asString());	
}