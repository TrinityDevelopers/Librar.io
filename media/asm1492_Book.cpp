#include "asm1492_Book.h"


string Book::get_formatted_copyright_year() const {
	if(copyright_year != -1)
		return "©" + std::to_string(copyright_year);
	return "Unknown";
}

string Book::to_string() const {
	stringstream stm;
	stm << Media::to_string();
	stm << setw(18) << left << "Author: " << author << endl;
	stm << setw(18) << left << "Copyright: " << get_formatted_copyright_year() << endl;
	stm << setw(18) << left << "Page Count: " << page_count << endl;
	return stm.str();
}

ostream& operator<<(ostream& ost, const Book& book_two) {
	ost << book_two.to_string();
	return ost;
}