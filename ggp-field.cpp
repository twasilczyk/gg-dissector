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

GGPField::GGPField(const GGPField &obj):
	GGPField(obj.name, obj.abbrev, obj.blurb)
{
	hf_id = obj.hf_id;
}

GGPField::~GGPField()
{
	for (auto it = all_fields.begin(); it != all_fields.end(); it++) {
		if (*it == this) {
			all_fields.erase(it);
			break;
		}
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
	base = BASE_DEC;
}

void
GGPFieldUINT32::fill_header_field_info(header_field_info &info)
{
	info.type = FT_UINT32;
	info.display = base;
}

GGPFieldHEX32::GGPFieldHEX32(const char *name, const char *abbrev, const char *blurb):
	GGPFieldUINT32(name, abbrev, blurb)
{
	base = BASE_HEX;
}

GGPFieldHEX64::GGPFieldHEX64(const char *name, const char *abbrev, const char *blurb):
	GGPField(name, abbrev, blurb)
{
}

void
GGPFieldHEX64::fill_header_field_info(header_field_info &info)
{
	info.type = FT_UINT64;
	info.display = BASE_HEX;
}

GGPFieldEnum32::GGPFieldEnum32(const char *name, const char *abbrev, const char *blurb,
	const value_string *vals):
	GGPField(name, abbrev, blurb),vals(vals)
{
}

void
GGPFieldEnum32::fill_header_field_info(header_field_info &info)
{
	info.type = FT_UINT32;
	info.display = BASE_HEX;
	info.strings = vals;
}

GGPFieldBlob::GGPFieldBlob(const char *name, const char *abbrev, const char *blurb):
	GGPField(name, abbrev, blurb)
{
}

void
GGPFieldBlob::fill_header_field_info(header_field_info &info)
{
	info.type = FT_BYTES;
	info.display = BASE_NONE;
}

GGPFieldString::GGPFieldString(const char *name, const char *abbrev, const char *blurb):
	GGPField(name, abbrev, blurb)
{
}

void
GGPFieldString::fill_header_field_info(header_field_info &info)
{
	info.type = FT_STRING;
	info.display = BASE_NONE;
}
