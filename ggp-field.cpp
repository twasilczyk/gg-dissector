#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "ggp-field.hpp"

#include <iostream>
#include <mutex>

#define MAX_FIELDS 100

using namespace std;

vector<GGPField*> GGPField::all_fields;

GGPField::GGPField(const char *name, const char *abbrev, const char *blurb):
	name(name),abbrev(abbrev),blurb(blurb),hf_id(-1)
{
	all_fields.push_back(this);
}

GGPField::~GGPField()
{
	for (auto it = all_fields.begin(); it != all_fields.end(); it++) {
		if (*it == this)
			all_fields.erase(it);
	}
}

GGPField::operator int()
{
	return this->hf_id;
}

void
GGPField::register_all(int parent)
{
	static hf_register_info hf[MAX_FIELDS];
	header_field_info empty = {
		NULL, NULL, FT_NONE, 0, NULL, 0, NULL,
		HFILL
	};

	assert(MAX_FIELDS >= all_fields.size());

	int i = 0;
	for (auto f : all_fields) {
		assert(i < MAX_FIELDS);

		hf[i].p_id = &f->hf_id;
		hf[i].hfinfo = empty;

		hf[i].hfinfo.name = f->name;
		hf[i].hfinfo.abbrev = f->abbrev;
		hf[i].hfinfo.blurb = f->blurb;

		f->fill_header_field_info(hf[i].hfinfo);

		i++;
	}
	proto_register_field_array(parent, hf, i);
}

GGPFieldUINT32::GGPFieldUINT32(const char *name, const char *abbrev, const char *blurb):
	GGPField(name, abbrev, blurb)
{
}

void
GGPFieldUINT32::fill_header_field_info(header_field_info &info)
{
	info.type = FT_UINT32;
	info.display = BASE_DEC;
}
