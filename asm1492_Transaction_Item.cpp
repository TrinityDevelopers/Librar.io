#include "asm1492_Transaction_Item.h"

#include "asm1492_Bundle.h"
#include "media/asm1492_Media.h"

bool Transaction_Item::is_overdue(Date current) {
	if(due_date < current)
		return true;
	return false;
}

string Transaction_Item::to_string() {
	stringstream stm;
	if(bundle != NULL)
		stm << bundle->to_compact_string() << endl;
	else if(media != NULL)
		stm << media->to_compact_string() << endl;
	stm << "Due Date: " << due_date.to_string() << endl;
	return stm.str();
}

double Transaction_Item::calculate_fee(Date check_in) {
	if(!is_overdue(check_in))
		return 0.0;
	if(bundle != NULL)
		return (*(bundle->get_medias().begin()))->get_daily_fee() * due_date.days_late(check_in);
	else if(media != NULL) {
		int fee = media->get_daily_fee() * due_date.days_late(check_in);
		return fee;
	}
	return 0.0;
}

bool Transaction_Item::contains(Bundle* bundle_) {
	return this->bundle == bundle_;
}

bool Transaction_Item::contains(Media* media_) {
	return this->media == media_;
}