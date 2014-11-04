#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "dissect-protobuf.hpp"

#include "ggp-field.hpp"

using namespace std;

static GGPFieldBlob protobuf_blob
	("unknown string", "gg.unknown_string", NULL);
static GGPFieldBlob protobuf_varint
	("unknown varint", "gg.unknown_varint", NULL);
static GGPFieldUINT32 protobuf_fixedint
	("unknown fixedint", "gg.unknown_fixedint", NULL);
static GGPFieldHEX64 protobuf_fixedint64
	("unknown fixedint64", "gg.unknown_fixedint64", NULL);

static gint64
parse_varint(tvbuff_t *tvb, int &&offset = 0)
{
	guint64 val = 0;
	guint64 shift = 0;
	bool more = true;

	while (more) {
		DISSECTOR_ASSERT(tvb_length_remaining(tvb, offset) > 0);
		DISSECTOR_ASSERT(shift <= 64 - 7);

		guint64 b = tvb_get_guint8(tvb, offset++);

		more = b & 0x80;
		b &= ~0x80;

		b <<= shift;
		shift += 7;

		val |= b;
	}

	return val;
}

class PBDisplayUnknownFixedint : public PBDisplay
{
public:
	PBDisplayUnknownFixedint():PBDisplay(PBTYPE_FIXED32) {}

	virtual void display(proto_tree *tree, tvbuff_t *tvb, int id)
	{
		guint32 val = tvb_get_letohl(tvb, 0);
		proto_tree_add_uint_format(tree, protobuf_fixedint, tvb, 0, 4, val,
			"unknown field %d: %d", id, val);
	}
};

class PBDisplayUnknownFixedint64 : public PBDisplay
{
public:
	PBDisplayUnknownFixedint64():PBDisplay(PBTYPE_FIXED64) {}

	virtual void display(proto_tree *tree, tvbuff_t *tvb, int id)
	{
		DISSECTOR_ASSERT(tvb_length(tvb) == 8);

		guint64 val = tvb_get_letoh64(tvb, 0);
		proto_tree_add_uint64_format(tree, protobuf_fixedint64, tvb, 0, 8, val,
			"unknown field %d: %" G_GUINT64_FORMAT, id, val);
	}
};

class PBDisplayUnknownVarint : public PBDisplay
{
public:
	PBDisplayUnknownVarint():PBDisplay(PBTYPE_VARINT) {}

	virtual void display(proto_tree *tree, tvbuff_t *tvb, int id)
	{
		guint64 val = parse_varint(tvb, 0);

		proto_tree_add_bytes_format(tree, protobuf_varint, tvb,
			0, tvb_length(tvb), NULL,
			"unknown field %d: %" G_GUINT64_FORMAT, id, val);
	}
};

class PBDisplayUnknownBlob : public PBDisplay
{
public:
	PBDisplayUnknownBlob():PBDisplay(PBTYPE_STRING) {}

	virtual void display(proto_tree *tree, tvbuff_t *tvb, int id)
	{
		proto_tree_add_bytes_format(tree, protobuf_blob, tvb, 0, tvb_length(tvb), NULL,
			"unknown field %d: string[%d]", id, tvb_length(tvb));
	}
};

PBDisplay::PBDisplay(PBType expected_type):expected_type(expected_type)
{
}

void PBDisplay::display(proto_tree *tree, tvbuff_t *tvb, int id, PBType type)
{
	DISSECTOR_ASSERT(type == expected_type);

	this->display(tree, tvb, id);
}

void PBDisplay::display(proto_tree *tree, tvbuff_t *tvb, int /* id */)
{
	this->display(tree, tvb);
}

void PBDisplay::display(proto_tree*, tvbuff_t*)
{
	DISSECTOR_ASSERT_NOT_REACHED();
}

static PBDisplayUnknownVarint displayVarint;
static PBDisplayUnknownFixedint displayFixedint;
static PBDisplayUnknownFixedint64 displayFixedint64;
static PBDisplayUnknownBlob displayBlob;

void dissect_protobuf(tvbuff_t *tvb, proto_tree *tree)
{
	vector<shared_ptr<PBDisplay>> empty(0);

	dissect_protobuf(tvb, tree, empty);
}

void
dissect_protobuf(tvbuff_t *tvb, proto_tree *tree, vector<shared_ptr<PBDisplay>> &packet_desc)
{
	gint offset = 0;

	while (tvb_length_remaining(tvb, offset) > 0) {
		gint64 header = parse_varint(tvb, move(offset));
		guint8 type = header & 7;
		guint id = header >> 3;
		PBDisplay *displayer = NULL;
		tvbuff_t *sub_tvb = NULL;

		if (type == 0) {
			gint original_offset = offset;
			parse_varint(tvb, move(offset));

			sub_tvb = tvb_new_subset_length(tvb,
				original_offset, offset - original_offset);

			displayer = &displayVarint;
		} else if (type == 1) {
			DISSECTOR_ASSERT(tvb_length_remaining(tvb, offset) >= 8);

			sub_tvb = tvb_new_subset_length(tvb, offset, 8);
			offset += 8;

			displayer = &displayFixedint64;
		} else if (type == 2) {
			guint8 length = parse_varint(tvb, move(offset));

			DISSECTOR_ASSERT(tvb_length_remaining(tvb, offset) >= length);

			sub_tvb = tvb_new_subset_length(tvb, offset, length);
			offset += length;

			displayer = &displayBlob;
		} else if (type == 5) {
			DISSECTOR_ASSERT(tvb_length_remaining(tvb, offset) >= 4);

			sub_tvb = tvb_new_subset_length(tvb, offset, 4);
			offset += 4;

			displayer = &displayFixedint;
		} else
			DISSECTOR_ASSERT_NOT_REACHED();

		if (id > 0 && id <= packet_desc.size())
			displayer = packet_desc[id - 1].get();

		displayer->display(tree, sub_tvb, id, static_cast<PBType>(type));
	}
}

PBDisplayUnknown::PBDisplayUnknown():PBDisplay(PBTYPE_VARINT)
{
}
void PBDisplayUnknown::display(proto_tree *tree, tvbuff_t *tvb, int id, PBType type)
{
	switch (type) {
		case PBTYPE_VARINT:
			displayVarint.display(tree, tvb, id);
			return;
		case PBTYPE_FIXED64:
			displayFixedint64.display(tree, tvb, id);
			return;
		case PBTYPE_STRING:
			displayBlob.display(tree, tvb, id);
			return;
		case PBTYPE_FIXED32:
			displayFixedint.display(tree, tvb, id);
			return;
	}
	DISSECTOR_ASSERT_NOT_REACHED();
}

PBDisplayUINT32::PBDisplayUINT32(GGPFieldUINT32 field):PBDisplay(PBTYPE_FIXED32),field(field) {};
void PBDisplayUINT32::display(proto_tree *tree, tvbuff_t *tvb)
{
	proto_tree_add_uint(tree, field, tvb, 0, 4, tvb_get_letohl(tvb, 0));
};

PBDisplayTimestamp::PBDisplayTimestamp(GGPFieldTimestamp field):PBDisplay(PBTYPE_FIXED32),field(field) {};
void PBDisplayTimestamp::display(proto_tree *tree, tvbuff_t *tvb)
{
	nstime_t data;

	data.secs = tvb_get_letohl(tvb, 0);
	data.nsecs = 0;

	proto_tree_add_time(tree, field, tvb, 0, 4, &data);
};

PBDisplayVITimestamp::PBDisplayVITimestamp(GGPFieldTimestamp field):PBDisplayTimestamp(field)
{
	expected_type = PBTYPE_VARINT;
};
void PBDisplayVITimestamp::display(proto_tree *tree, tvbuff_t *tvb)
{
	nstime_t data;

	data.secs = parse_varint(tvb);
	data.nsecs = 0;

	proto_tree_add_time(tree, field, tvb, 0, tvb_length(tvb), &data);
};

PBDisplayUINT64::PBDisplayUINT64(GGPFieldHEX64 field):PBDisplay(PBTYPE_FIXED64),field(field) {};
void PBDisplayUINT64::display(proto_tree *tree, tvbuff_t *tvb)
{
	proto_tree_add_uint64(tree, field, tvb, 0, 8, tvb_get_letoh64(tvb, 0));
};

PBDisplayVarint::PBDisplayVarint(GGPFieldUINT64 field):PBDisplay(PBTYPE_VARINT),field(field) {};
void PBDisplayVarint::display(proto_tree *tree, tvbuff_t *tvb)
{
	proto_tree_add_uint64(tree, field, tvb, 0, tvb_length(tvb), parse_varint(tvb));
};

PBDisplayEnum::PBDisplayEnum(GGPFieldEnum field):PBDisplayVarint(field)
{
};
void PBDisplayEnum::display(proto_tree *tree, tvbuff_t *tvb)
{
	proto_tree_add_item(tree, field, tvb, 0, tvb_length(tvb), parse_varint(tvb));
};


PBDisplayUIN::PBDisplayUIN(GGPFieldString field):PBDisplay(PBTYPE_STRING),field(field) {};
void PBDisplayUIN::display(proto_tree *tree, tvbuff_t *tvb)
{
	guint8 magic = tvb_get_guint8(tvb, 0);
	guint8 length = tvb_get_guint8(tvb, 1);

	DISSECTOR_ASSERT((uint)length + 2 == tvb_length(tvb));

	const char *value = (const gchar*)tvb_get_ephemeral_string(tvb, 2, length);

	proto_tree_add_string_format_value(tree, field, tvb, 2, length, value,
		"%s (%d)", value, magic);
};

PBDisplayString::PBDisplayString(GGPFieldString field):PBDisplay(PBTYPE_STRING),field(field) {};
void PBDisplayString::display(proto_tree *tree, tvbuff_t *tvb)
{
	proto_tree_add_item(tree, field, tvb, 0, tvb_length(tvb), 0);
};

PBDisplayBlob::PBDisplayBlob(GGPFieldBlob field):PBDisplay(PBTYPE_STRING),field(field) {};
void PBDisplayBlob::display(proto_tree *tree, tvbuff_t *tvb)
{
	proto_tree_add_item(tree, field, tvb, 0, tvb_length(tvb), 0);
};
