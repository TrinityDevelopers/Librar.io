#include "asm1492_Movie.h"

#include "../asm1492_Date.h"

string Movie::to_string() const {
	stringstream stm;
	stm << Media::to_string();
	stm << setw(18) << left << "Release Year: " << release_year << endl;
	stm << setw(18) << left << "Producer: " << producer << endl;
	stm << setw(18) << left << "Director: " << director << endl;
	stm << setw(18) << left << "Lead Actors: ";
	for(auto it = leading_actors.begin(); it != leading_actors.end(); it++) {
		if(it != leading_actors.begin()) stm << ", ";
		stm << *it;
	}
	stm << setw(18) << left << endl;
	stm << setw(18) << left << "Runtime: " << runtime << " Minutes" << endl;
	return stm.str();
}

ostream& operator<<(ostream& ost, const Movie& movie_two) {
	ost << movie_two.to_string();
	return ost;
}

Date Movie::get_due_date(Date check_out_date) {
	check_out_date.add_days(7);
	return check_out_date;
}

double Movie::get_daily_fee() {
	return 1.00;
}