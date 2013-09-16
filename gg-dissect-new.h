#ifndef _GG_DISSECT_NEW_H
#define _GG_DISSECT_NEW_H

#include "packet-gg.h"

extern int gg_dissect_hf_uin;
extern int gg_dissect_hf_uin_s;
extern int gg_dissect_hf_uin_s_len;
extern int gg_dissect_hf_seq_out;
extern int gg_dissect_hf_imtoken_len;
extern int gg_dissect_hf_imtoken;
extern int gg_dissect_hf_mpa_seq;
extern int gg_dissect_hf_mpa_data;
extern int gg_dissect_hf_mpa_data_len;

#define GG_DISSECT_NEW_HF \
	{ &gg_dissect_hf_uin, \
		{ "User identifier", "gg.packet.uin", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_hf_uin_s, \
		{ "User identifier", "gg.packet.uin_s", \
		FT_STRING, BASE_NONE, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_hf_uin_s_len, \
		{ "User identifier length", "gg.packet.uin_s.len", \
		FT_UINT8, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_hf_seq_out, \
		{ "Sequence number (out)", "gg.packet.seq.out", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	\
	{ &gg_dissect_hf_imtoken_len, \
		{ "IMToken length", "gg.packet.imtoken.len", \
		FT_UINT8, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_hf_imtoken, \
		{ "IMToken", "gg.packet.imtoken", \
		FT_STRING, BASE_NONE, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	\
	{ &gg_dissect_hf_mpa_seq, \
		{ "MPA sequence number", "gg.packet.mpa.seq", \
		FT_UINT8, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_hf_mpa_data_len, \
		{ "MPA data length", "gg.packet.mpa.data.len", \
		FT_UINT8, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_hf_mpa_data, \
		{ "MPA data", "gg.packet.mpa.data", \
		FT_STRING, BASE_NONE, \
		NULL, 0, \
		NULL, HFILL } \
	}, \

void gg_dissect_imtoken(tvbuff_t *tvb, proto_tree *tree);

void gg_dissect_mpa_notify(tvbuff_t *tvb, proto_tree *tree);
void gg_dissect_mpa_ack(tvbuff_t *tvb, proto_tree *tree);

void gg_dissect_chat_info(tvbuff_t *tvb, proto_tree *tree);

#endif /* _GG_DISSECT_NEW_H */
