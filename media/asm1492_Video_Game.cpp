#include "asm1492_Video_Game.h"

string Video_Game::to_string() const {
	stringstream stm;
	stm << Media::to_string();
	stm << setw(18) << left << "Release Year: " << release_year << endl;
	stm << setw(18) << left << "Studio: " << studio << endl;
	return stm.str();
}

ostream& operator<<(ostream& ost, const Video_Game& game_two) {
	ost << game_two.to_string();
	return ost;
}

double Video_Game::get_daily_fee() {
	return 1.00;
}

void Video_Game::save(Json::Value& game) {
	Media::save(game);
	game["release_year"] = release_year;
	game["studio"] = studio;
}

void Video_Game::load(Json::Value& game) {
	Media::load(game);
	release_year = game.get("release_year", -1).asInt();
	studio = game.get("studio", "unknown").asString();
}