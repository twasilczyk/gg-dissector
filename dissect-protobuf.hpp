extern "C" {
#include <epan/packet.h>
}

void dissect_protobuf(tvbuff_t *tvb, proto_tree *tree);
