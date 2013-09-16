#ifndef _GG_DISSECT_USERLIST_H
#define _GG_DISSECT_USERLIST_H

#include "packet-gg.h"

extern int gg_dissect_userlist_hf_type; //TODO: list of values
extern int gg_dissect_userlist_hf_version;
extern int gg_dissect_userlist_hf_format;
extern int gg_dissect_userlist_hf_request;

#define GG_DISSECT_USERLIST_HF \
	{ &gg_dissect_userlist_hf_type, \
		{ "query type", "gg.packet.userlist.type", \
		FT_UINT8, BASE_HEX, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_userlist_hf_version, \
		{ "buddy list version", "gg.packet.userlist.version", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_userlist_hf_format, \
		{ "format", "gg.packet.userlist.format", \
		FT_UINT8, BASE_HEX, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_userlist_hf_request, \
		{ "request", "gg.packet.userlist.request", \
		FT_STRING, BASE_NONE, \
		NULL, 0, \
		NULL, HFILL } \
	}, \

extern void gg_dissect_userlist100_version(tvbuff_t *tvb, proto_tree *tree);

extern void gg_dissect_userlist100_request(tvbuff_t *tvb, proto_tree *tree, packet_info *pinfo);

#endif /*_GG_DISSECT_USERLIST_H*/
