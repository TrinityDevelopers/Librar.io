#include "asm1492_Transaction_Item.h"

#include "asm1492_Bundle.h"
#include "media/asm1492_Media.h"
#include "asm1492_Library.h"

bool Transaction_Item::is_overdue(Date current) {
	return due_date < current;
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
	if(this->bundle != NULL)
		return this->bundle == bundle_;
	return false;
}

bool Transaction_Item::contains(Media* media_) {
	if(this->media != NULL)
		return this->media == media_;
	return false;
}

void Transaction_Item::save(Json::Value& item) {
	if(bundle != NULL)
		item["bundle"] = bundle->get_name();
	else if(media != NULL)
		item["media"] = media->get_id_number();
	Json::Value date;
	due_date.save(date);
	item["due_date"] = date;
}

Transaction_Item Transaction_Item::load(Json::Value& item) {
	Date due_date = Date::load(item["due_date"]);
	if(!item["bundle"].isNull())
		return Transaction_Item(Library::get_bundle(item["bundle"].asString()), due_date);
	else if(!item["media"].isNull())
		return Transaction_Item(Library::get_media(item["media"].asInt()), due_date);
}