#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "dissect-gg11.hpp"

#include "ggp-field.hpp"

static GGPFieldBlob login105_test
	("test", "gg.test", NULL);

void dissect_gg11_login105(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, login105_test, tvb, 0, tvb_length(tvb), FALSE);
}
