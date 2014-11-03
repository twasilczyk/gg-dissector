#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "dissect-gg11.hpp"

#include "dissect-protobuf.hpp"

#include <vector>

using namespace std;

static vector<shared_ptr<PBDisplay>> packet_login105 = {
	make_shared<PBDisplayString>(GGPFieldString("language", "gg.login105.language", NULL))
};

void dissect_gg11_login105(tvbuff_t *tvb, proto_tree *tree)
{
	dissect_protobuf(tvb, tree, packet_login105);
}
