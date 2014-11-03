#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "dissect-gg11.hpp"

#include "dissect-protobuf.hpp"

#include <vector>

using namespace std;

static vector<shared_ptr<PBDisplay>> packet_login105 = {
	make_shared<PBDisplayString>(GGPFieldString("language", "gg.login105.language", NULL)),
	make_shared<PBDisplayUIN>(GGPFieldString("uin", "gg.login105.uin", NULL)),
	make_shared<PBDisplayBlob>(GGPFieldBlob("hash", "gg.login105.hash", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT32("dummy1", "gg.login105.dummy1", NULL)),
	make_shared<PBDisplayUINT32>(GGPFieldHEX32("dummy2", "gg.login105.dummy2", NULL)),
	make_shared<PBDisplayUINT32>(GGPFieldHEX32("dummy3", "gg.login105.dummy3", NULL)),
	make_shared<PBDisplayString>(GGPFieldString("client", "gg.login105.client", NULL)),
	make_shared<PBDisplayUINT32>(GGPFieldHEX32("initial_status", "gg.login105.initial_status", NULL)),
	make_shared<PBDisplayString>(GGPFieldString("initial_descr", "gg.login105.initial_descr", NULL)),
	make_shared<PBDisplayBlob>(GGPFieldBlob("dummy4", "gg.login105.dummy4", NULL)),
	make_shared<PBDisplayString>(GGPFieldString("supported_features", "gg.login105.supported_features", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT32("dummy5", "gg.login105.dummy5", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT32("dummy6", "gg.login105.dummy6", NULL)),
	make_shared<PBDisplayUINT32>(GGPFieldUINT32("dummy7", "gg.login105.dummy7", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT32("dummy8", "gg.login105.dummy8", NULL)),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayVarint>(GGPFieldUINT32("dummy10", "gg.login105.dummy10", NULL)),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayBlob>(GGPFieldBlob("dummy15", "gg.login105.dummy15", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT32("dummy16", "gg.login105.dummy16", NULL)),
	make_shared<PBDisplayBlob>(GGPFieldBlob("dummy17", "gg.login105.dummy17", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT32("dummy18", "gg.login105.dummy18", NULL)),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayBlob>(GGPFieldBlob("dummy21", "gg.login105.dummy21", NULL)),
};

void dissect_gg11_login105(tvbuff_t *tvb, proto_tree *tree)
{
	dissect_protobuf(tvb, tree, packet_login105);
}
