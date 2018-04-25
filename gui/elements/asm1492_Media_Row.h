#pragma once

#include "asm1492_Catalog_Row.h"

#include "../../media/asm1492_Media.h"

class Media_Row : public Catalog_Row {
public:
	Media_Row(Media* media_, Date due_date = Date::empty_date);
	Media* get_media() { return media; };
	
private:
	Glib::RefPtr<Gdk::Pixbuf> icon_from_format(Media::Format form);

	Media* media;
};