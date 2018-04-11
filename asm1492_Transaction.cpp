#include "asm1492_Transaction.h"

#include "media/asm1492_Media.h"
#include "asm1492_Bundle.h"
#include "asm1492_Transaction_Item.h"
#include "asm1492_Customer.h"
#include "asm1492_Librarian.h"

Transaction::Transaction(int trans_num, Date check_out, Librarian* lib, Customer* cust, vector<Media*> media, vector<Bundle*> bundle)
	: transaction_number(trans_num), check_out_date(check_out), librarian(lib), customer(cust) {
	
	for(Media* med : media) {
		Transaction_Item* item = new Transaction_Item(med, med->get_due_date(check_out));
		items.push_back(item);
		cust->add_transaction_item(item);
	}
	for(Bundle* bun : bundle) {
		Transaction_Item* item = new Transaction_Item(bun, (*(bun->get_medias().begin()))->get_due_date(check_out));
		items.push_back(item);
		cust->add_transaction_item(item);
	}
}

string Transaction::to_string() {
	stringstream stm;
	stm << "Transaction Number: " << transaction_number << endl;
	stm << "Check-Out Date:     " << check_out_date.to_string() << endl;
	stm << "Librarian:          " << librarian->to_compact_string() << endl;
	stm << "Customer:           " << customer->to_compact_string() << endl << endl;
	stm << "Checked Out Items:" << endl << endl;
	for(Transaction_Item* item : items)
		stm << item->to_string() << endl;
	return stm.str();
}