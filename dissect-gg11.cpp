#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "dissect-gg11.hpp"

#include "dissect-protobuf.hpp"

#include <vector>

using namespace std;

GGPFieldBlob field_language("language", "gg.login105.language", NULL);

static vector<PBDisplay*> packet_login105 = {
	new PBDisplayString(&field_language)
};

void dissect_gg11_login105(tvbuff_t *tvb, proto_tree *tree)
{
	dissect_protobuf(tvb, tree, packet_login105);
}
