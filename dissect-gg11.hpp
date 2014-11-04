extern "C" {
#include <epan/packet.h>
}

void init_gg11();

void dissect_gg11_login105(tvbuff_t *tvb, proto_tree *tree);
void dissect_gg11_login105_ok(tvbuff_t *tvb, proto_tree *tree);
void dissect_gg11_send_msg110(tvbuff_t *tvb, proto_tree *tree);
void dissect_gg11_recv_msg110(tvbuff_t *tvb, proto_tree *tree);
void dissect_gg11_imtoken(tvbuff_t *tvb, proto_tree *tree);
void dissect_gg11_options(tvbuff_t *tvb, proto_tree *tree);
void dissect_gg11_lastdates(tvbuff_t *tvb, proto_tree *tree);
void dissect_gg11_mpanotify(tvbuff_t *tvb, proto_tree *tree);
