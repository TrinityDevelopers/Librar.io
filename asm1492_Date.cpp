#include "asm1492_Date.h"

Date Date::empty_date = {0, 0, 0};

tm* Date::get_current_time() {
	time_t rawtime;
	tm* tminfo;
	time(&rawtime);
	tminfo = localtime(&rawtime);
	return tminfo;
}

Date Date::get_current_date(tm* tminfo) {
	return {tminfo->tm_year + 1900, tminfo->tm_mon + 1, tminfo->tm_mday};
}

Date Date::load(Json::Value& date) {
	return {date.get("year", 2000).asInt(), date.get("month", 1).asInt(), date.get("day", 1).asInt()};
}

void Date::save(Json::Value& date) {
	date["year"] = year;
	date["month"] = month;
	date["day"] = day;
}

void Date::add_days(int days) {
	tm* tminfo = get_current_time();
	tminfo->tm_year = year - 1900;
	tminfo->tm_mon = month - 1;
	tminfo->tm_mday = day + days;
	mktime(tminfo);

	year = tminfo->tm_year + 1900;
	month = tminfo->tm_mon + 1;
	day = tminfo->tm_mday;
}

int Date::days_late(Date check_in) {
	tm* tminfo = get_current_time();
	tminfo->tm_year = year - 1900;
	tminfo->tm_mon = month - 1;
	tminfo->tm_mday = day;
	mktime(tminfo);
	int due_date = tminfo->tm_yday;
	tminfo->tm_year = check_in.year - 1900;
	tminfo->tm_mon = check_in.month - 1;
	tminfo->tm_mday = check_in.day;
	mktime(tminfo);
	int check_in_date = tminfo->tm_yday;
	return check_in_date - due_date;
}

bool Date::operator<(const Date& date_two) const {
	if(this->year < date_two.year)
		return true;
	if(this->year > date_two.year)
		return false;
    if(this->month < date_two.month)
        return true;
    if(this->month > date_two.month)
        return false;
    if(this->day < date_two.day)
        return true;
    return false;
}

string Date::to_string() {
	stringstream stm;
	stm << setfill('0') << setw(2) << month << "/";
	stm << setfill('0') << setw(2) << day << "/";
	stm << setfill('0') << setw(4) << year;
	return stm.str();
}