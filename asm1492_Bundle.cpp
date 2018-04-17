#include "asm1492_Bundle.h"

#include "asm1492_Library.h"

Bundle::Bundle(string name_, vector<Media*> medias_) : name(name_), medias{}, checked_out(false) {
	for(Media* media : medias_)
		add(media);
}

bool Bundle::add(Media* media) {
	media->add_to_bundle(this);
	return medias.insert(media).second;
}

bool Bundle::add(int id) {
	Media* media = Library::get_media(id);
	if(!media)
		return false;
	return add(media);
}

bool Bundle::remove(Media* media) {
	media->remove_from_bundle();
	return medias.erase(media);
}

bool Bundle::remove(int id) {
	for(Media* media : medias) {
		if(media->get_id_number() == id) {
			media->remove_from_bundle();
			return medias.erase(media);	
		}
	}
	return false;
}

void Bundle::check_out() {
	if(!checked_out) {
		checked_out = true;
		for(Media* media : medias) {
			media->check_out();
		}
	}
}

void Bundle::check_in() {
	if(checked_out) {
		checked_out = false;
		for(Media* media : medias) {
			media->check_in();
		}
	}
}

void Bundle::set_checked_out() {
	checked_out = true;
}

void Bundle::set_checked_in() {
	for(Media* media : medias) {
		if(media->is_checked_out())
			return;
	}
	checked_out = false;
}

string Bundle::to_compact_string() {
	stringstream stm;
	stm << "Bundle Name: " << name;
	stm << "\tContained Media: ";
	for(Media* media : medias)
		stm << media->get_id_number() << " ";
	return stm.str();
}

ostream& operator<<(ostream& ost, const Bundle& bundle_two) {
	ost << "Bundle Name: " << bundle_two.name << endl;
	ost << "Checkout status: " << (bundle_two.checked_out ? "Checked Out" : "Checked In") << endl;
	ost << "Contained Media: " << endl;
	for(Media* media : bundle_two.medias) {
		ost << "\t" << media->to_compact_string() << endl;
	}
	return ost;
}

void Bundle::save(Json::Value& bundle) {
	bundle["name"] = name;
	Json::Value media_list;
	for(Media* media : medias) {
		media_list.append(media->get_id_number());
	}
	bundle["medias"] = media_list;
	bundle["checked_out"] = checked_out;
}

string Bundle::get_medias_string() {
	stringstream stm;
	for(auto it = medias.begin(); it != medias.end(); it++) {
		if(it != medias.begin()) stm << ", ";
		stm << (*it)->get_id_number();
	}
	return stm.str();
}