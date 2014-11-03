extern "C" {
#include <epan/packet.h>
}

void dissect_gg11_login105(tvbuff_t *tvb, proto_tree *tree);
void dissect_gg11_send_msg110(tvbuff_t *tvb, proto_tree *tree);
void dissect_gg11_recv_msg110(tvbuff_t *tvb, proto_tree *tree);
