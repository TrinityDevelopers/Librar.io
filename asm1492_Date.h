#pragma once

#include <ctime>
#include <sstream>
#include <iomanip>

#include "json/asm1492_json.h"

using namespace std;

class Date {
public:
	Date(int y, int m, int d) : year(y), month(m), day(d) {};
	
	void add_days(int days);
	int days_late(Date check_in);
	bool operator<(const Date& date_two) const;

	string to_string();

	void save(Json::Value&);
	static Date load(Json::Value&);

	static tm* get_current_time();
	static Date get_current_date(tm* tminfo = get_current_time());
	static Date empty_date;
	
private:
	int year;
	int month;
	int day;
};