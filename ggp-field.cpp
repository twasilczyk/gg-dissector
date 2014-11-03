#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "ggp-field.hpp"

#define MAX_FIELDS 100

using namespace std;

vector<GGPField*> GGPField::all_fields;

GGPField::GGPField()
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

void
GGPField::register_all(int parent)
{
	static hf_register_info hf[MAX_FIELDS];

	assert(MAX_FIELDS >= all_fields.size());

	int i = 0;
	for (auto f : all_fields) {
		assert(i < MAX_FIELDS);

		hf[i].p_id = &f->hf_id;
		hf[i].hfinfo = f->get_header_field_info();

		i++;
	}

	proto_register_field_array(parent, hf, i);
}
