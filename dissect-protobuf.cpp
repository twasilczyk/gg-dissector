#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "dissect-protobuf.hpp"

#include "ggp-field.hpp"

static GGPFieldBlob protobuf_blob
	("unknown string", "gg.protobuf_unknown_string", NULL);
static GGPFieldBlob protobuf_varint
	("unknown varint", "gg.protobuf_unknown_varint", NULL);
static GGPFieldUINT32 protobuf_fixedint
	("unknown fixedint", "gg.protobuf_unknown_fixedint", NULL);

class ProtobufDissector
{
private:
	gint offset = 0;
	tvbuff_t *tvb;
	proto_tree *tree;

public:
	ProtobufDissector(tvbuff_t *tvb, proto_tree *tree):
		tvb(tvb),tree(tree)
	{
	}

	bool still_remaining() const
	{
		return (tvb_length_remaining(tvb, offset) > 0);
	}

	void dissect_fixedint(int id)
	{
		guint32 val = tvb_get_letohl(tvb, offset);

		proto_tree_add_uint_format(tree, protobuf_fixedint, tvb, offset, 4, val,
			"unknown field %d: %d", id, val);

		offset += 4;
	}

	void dissect_varint(int id)
	{
		guint8 val = tvb_get_guint8(tvb, offset); //TODO: varint

		proto_tree_add_bytes_format(tree, protobuf_varint, tvb, offset, 1, NULL,
			"unknown field %d: %d", id, val);

		offset += 1;
	}

	void dissect_str(int id)
	{
		guint8 length = tvb_get_guint8(tvb, offset++); //TODO: varint

		DISSECTOR_ASSERT(tvb_length_remaining(tvb, offset) >= length);

		proto_tree_add_bytes_format(tree, protobuf_blob, tvb, offset, length, NULL,
			"unknown field %d: string[%d]", id, length);

		offset += length;
	}

	void dissect_more()
	{
		guint8 type = tvb_get_guint8(tvb, offset++);
		guint8 id = type >> 3;
		type &= 7;

		if (type == 0)
			dissect_varint(id);
		else if (type == 2)
			dissect_str(id);
		else if (type == 5)
			dissect_fixedint(id);
		else
			DISSECTOR_ASSERT_NOT_REACHED();
	}
};

void
dissect_protobuf(tvbuff_t *tvb, proto_tree *tree)
{
	ProtobufDissector pbdis(tvb, tree);

	while (pbdis.still_remaining()) {
		pbdis.dissect_more();
	}
}
