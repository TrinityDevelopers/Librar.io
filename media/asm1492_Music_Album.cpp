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