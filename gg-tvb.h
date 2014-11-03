#ifndef _GG_DISSECT_TVB_H
#define _GG_DISSECT_TVB_H

#include "packet-gg.h"

#include <epan/packet.h>

extern int gg_tvb_data;
extern int gg_tvb_byte;
extern int gg_tvb_packed_uint;

#define GG_TVB_HF \
	{ &gg_tvb_data, \
		{ "data", "gg.tvb.data", \
		FT_BYTES, BASE_NONE, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_tvb_byte, \
		{ "byte", "gg.tvb.byte", \
		FT_UINT8, BASE_HEX, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_tvb_packed_uint, \
		{ "packed uint", "gg.tvb.packed_uint", \
		FT_BYTES, BASE_NONE, \
		NULL, 0, \
		NULL, HFILL } \
	}, \

void gg_tvb_dissect(tvbuff_t *tvb, proto_tree *tree);

#endif /* _GG_DISSECT_TVB_H*/
