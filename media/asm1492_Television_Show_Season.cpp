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