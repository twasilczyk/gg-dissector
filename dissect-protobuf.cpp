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

static gint64
parse_varint(tvbuff_t *tvb, int &&offset = 0)
{
	gint64 val = 0;
	int val_len = 0;
	int shift = 0;
	bool more = true;

	while (more) {
		DISSECTOR_ASSERT(tvb_length_remaining(tvb, offset) > 0);
		DISSECTOR_ASSERT(++val_len <= 8);

		gint64 b = tvb_get_guint8(tvb, offset++);

		more = b & 0x80;
		b &= ~0x80;

		b <<= shift;
		shift += 7;

		val |= b;
	}

	return val;
}


PBDisplay::PBDisplay(int expected_type):expected_type(expected_type)
{
}

void PBDisplay::display(proto_tree *tree, tvbuff_t *tvb, int id, guint8 type)
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

PBDisplayFixedint::PBDisplayFixedint():PBDisplay(5) {}
void PBDisplayFixedint::display(proto_tree *tree, tvbuff_t *tvb, int id)
{
	guint32 val = tvb_get_letohl(tvb, 0);
	proto_tree_add_uint_format(tree, protobuf_fixedint, tvb, 0, 4, val,
		"unknown field %d: %d", id, val);
}

PBDisplayVarint::PBDisplayVarint():PBDisplay(0) {}
void PBDisplayVarint::display(proto_tree *tree, tvbuff_t *tvb, int id)
{
	gint val = parse_varint(tvb, 0);

	proto_tree_add_bytes_format(tree, protobuf_varint, tvb,
		0, tvb_length(tvb), NULL,
		"unknown field %d: %d", id, val);
}

PBDisplayBlob::PBDisplayBlob():PBDisplay(2) {}
void PBDisplayBlob::display(proto_tree *tree, tvbuff_t *tvb, int id)
{
	proto_tree_add_bytes_format(tree, protobuf_blob, tvb, 0, tvb_length(tvb), NULL,
		"unknown field %d: string[%d]", id, tvb_length(tvb));
}

void
dissect_protobuf(tvbuff_t *tvb, proto_tree *tree, vector<PBDisplay> &packet_desc)
{
	gint offset = 0;
	PBDisplayVarint displayVarint;
	PBDisplayFixedint displayFixedint;
	PBDisplayBlob displayBlob;

	while (tvb_length_remaining(tvb, offset) > 0) {
		gint64 header = parse_varint(tvb, move(offset));
		guint8 type = header & 7;
		gint id = header >> 3;
		PBDisplay *displayer = NULL;
		tvbuff_t *sub_tvb = NULL;

		if (type == 0) {
			gint original_offset = offset;
			parse_varint(tvb, move(offset));

			sub_tvb = tvb_new_subset_length(tvb,
				original_offset, offset - original_offset);

			displayer = &displayVarint;
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

		displayer->display(tree, sub_tvb, id);
	}
}
