#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "dissect-protobuf.hpp"

#include "ggp-field.hpp"

static GGPFieldBlob protobuf_test
	("testpb", "gg.testpb", NULL);

void dissect_protobuf(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, protobuf_test, tvb, 0, tvb_length(tvb), FALSE);
}
