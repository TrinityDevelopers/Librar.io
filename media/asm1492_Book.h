#pragma once

#include "asm1492_Media.h"

class Book : public Media {
public:
	Book(string title_, string genre_, string auth = "Unknown", int copyright = -1, int pages = 0)
		: Media(Format::Book, title_, genre_), author(auth), copyright_year(copyright), page_count(pages) {};

	string get_author() { return author; };
	int get_copyright_year() { return copyright_year; };
	int get_page_count() { return page_count; };
	string get_formatted_copyright_year() const;

	string to_string() const;
	friend ostream& operator<<(ostream& ost, const Book& book_two);
	
private:
	string author;
	int copyright_year;
	int page_count;
};