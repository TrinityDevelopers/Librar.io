#include "asm1492_Librarian.h"

#include "asm1492_Customer.h"
#include "media/asm1492_Media.h"
#include "asm1492_Bundle.h"
#include "asm1492_Transaction.h"
#include "asm1492_Transaction_Item.h"
#include "asm1492_Library.h"

#include <sstream>

Transaction* Librarian::check_out(Customer* customer, vector<Media*> medias, vector<Bundle*> bundles, Date check_out) {
	vector<Media*> check_out_medias;
	vector<Bundle*> check_out_bundles;
	for(Media* media : medias) {
		if(customer->can_check_out(media)) {
			media->check_out();
			check_out_medias.push_back(media);
		}
	}
	for(Bundle* bundle : bundles) {
		if(customer->can_check_out(bundle)) {
			bundle->check_out();
			check_out_bundles.push_back(bundle);
		}
	}
	Transaction* ret = Library::get_instance()->create_new_transaction(check_out, this, customer);
	ret->init(check_out_medias, check_out_bundles);
	return ret;
}

void Librarian::check_in(Customer* customer, vector<Media*> medias, vector<Bundle*> bundles, Date check_in) {
	for(Media* media : medias) {
		if(customer->is_checked_out(media)) {
			customer->remove_transaction_item(media, check_in);
			media->check_in();
		}
	}
	for(Bundle* bundle : bundles) {
		if(customer->is_checked_out(bundle)) {
			customer->remove_transaction_item(bundle, check_in);
			bundle->check_in();
		}
	}
}