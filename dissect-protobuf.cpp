#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "dissect-protobuf.hpp"

#include "ggp-field.hpp"

static GGPFieldBlob protobuf_blob
	("unknown string", "gg.protobuf_unknown_string", NULL);

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

	bool dissect_str(int id)
	{
		(void)id;

		guint8 length = tvb_get_guint8(tvb, offset++); //TODO: varint

		if (tvb_length_remaining(tvb, offset) < length)
			return false;

		proto_tree_add_item(tree, protobuf_blob, tvb, offset, length, FALSE);

		return true;
	}

	bool dissect_more()
	{
		guint8 type = tvb_get_guint8(tvb, offset++);
		guint8 id = type >> 3;
		type &= 7;

		if (type == 2) {
			return dissect_str(id);
		}

		return false;
	}
};

void
dissect_protobuf(tvbuff_t *tvb, proto_tree *tree)
{
	ProtobufDissector pbdis(tvb, tree);

	while (pbdis.still_remaining()) {
		if (!pbdis.dissect_more())
			break; // TODO: throw an error
	}
}
