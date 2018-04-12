#include "asm1492_Transaction.h"

#include "media/asm1492_Media.h"
#include "asm1492_Bundle.h"
#include "asm1492_Transaction_Item.h"
#include "asm1492_Customer.h"
#include "asm1492_Librarian.h"

void Transaction::init(vector<Media*> media, vector<Bundle*> bundle) {
	for(Media* med : media) {
		Transaction_Item item (med, med->get_due_date(check_out_date));
		items.push_back(item);
		customer->add_transaction_item(item);
	}
	for(Bundle* bun : bundle) {
		Transaction_Item item (bun, (*(bun->get_medias().begin()))->get_due_date(check_out_date));
		items.push_back(item);
		customer->add_transaction_item(item);
	}
}

void Transaction::add_transaction_item(Transaction_Item item) {
	items.push_back(item);
}

string Transaction::to_string() {
	stringstream stm;
	stm << "Transaction Number: " << transaction_number << endl;
	stm << "Check-Out Date:     " << check_out_date.to_string() << endl;
	stm << "Librarian:          " << librarian->to_compact_string() << endl;
	stm << "Customer:           " << customer->to_compact_string() << endl << endl;
	stm << "Checked Out Items:" << endl << endl;
	for(Transaction_Item item : items)
		stm << item.to_string() << endl;
	return stm.str();
}

void Transaction::save(Json::Value& transaction) {
	Json::Value date;
	check_out_date.save(date);
	transaction["check_out_date"] = date;
	transaction["librarian"] = librarian->get_id();
	transaction["customer"] = customer->get_id();
	Json::Value items_list;
	for(Transaction_Item trans_item : items) {
		Json::Value item;
		trans_item.save(item);
		items_list.append(item);
	}
	transaction["checked_out_items"] = items_list;
}