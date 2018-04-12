#include "asm1492_Television_Show_Season.h"

#include "../asm1492_Date.h"

string Television_Show_Season::to_string() const {
	stringstream stm;
	stm << Media::to_string();
	stm << setw(18) << left << "Release Year: " << release_year << endl;
	stm << setw(18) << left << "Producer: " << producer << endl;
	stm << setw(18) << left << "Directors: ";
	for(auto it = directors.begin(); it != directors.end(); it++) {
		if(it != directors.begin()) stm << ", ";
		stm << *it;
	}
	stm << endl;
	stm << setw(18) << left << "Lead Actors: ";
	for(auto it = leading_actors.begin(); it != leading_actors.end(); it++) {
		if(it != leading_actors.begin()) stm << ", ";
		stm << *it;
	}
	stm << endl;
	stm << setw(18) << left << "Runtime: " << runtime << " Minutes" << endl;
	stm << setw(18) << left << "Season: " << season_number << endl;
	return stm.str();
}

ostream& operator<<(ostream& ost, const Television_Show_Season& show_two) {
	ost << show_two.to_string();
	return ost;
}

Date Television_Show_Season::get_due_date(Date check_out_date) {
	check_out_date.add_days(7);
	return check_out_date;
}

double Television_Show_Season::get_daily_fee() {
	return 1.00;
}

void Television_Show_Season::save(Json::Value& show) {
	Media::save(show);
	show["release_year"] = release_year;
	show["producer"] = producer;
	Json::Value director_list;
	for(string director : directors)
		director_list.append(director);
	show["directors"] = director_list;
	Json::Value leads;
	for(string actor : leading_actors)
		leads.append(actor);
	show["leading_actors"] = leads;
	show["runtime"] = runtime;
	show["season_number"] = season_number;
}

void Television_Show_Season::load(Json::Value& show) {
	Media::load(show);
	release_year = show.get("release_year", -1).asInt();
	producer = show.get("producer", "unknown").asString();
	Json::Value director_list = show["directors"];
	for(int i = 0; i < director_list.size(); i++)
		directors.push_back(director_list[i].asString());
	Json::Value leads = show["leading_actors"];
	for(int i = 0; i < leads.size(); i++)
		leading_actors.push_back(leads[i].asString());
	runtime = show.get("runtime", 0).asDouble();
	season_number = show.get("season_number", 0).asInt();
}