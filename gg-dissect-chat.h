#ifndef _GG_DISSECT_CHAT_H
#define _GG_DISSECT_CHAT_H

#include "packet-gg.h"

extern int gg_dissect_hf_chat_id;
extern int gg_dissect_hf_chat_start;
extern int gg_dissect_hf_chat_dummy_date;
extern int gg_dissect_hf_chat_unknown;
extern int gg_dissect_hf_chat_version;
extern int gg_dissect_hf_chat_name_len;
extern int gg_dissect_hf_chat_name;
extern int gg_dissect_hf_chat_participants_count;
extern int gg_dissect_hf_chat_issuer;

#define GG_DISSECT_CHAT_HF \
	{ &gg_dissect_hf_chat_id, \
		{ "Chat ID", "gg.packet.chat_id", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_hf_chat_start, \
		{ "Conversation start", "gg.packet.chat.start", \
		FT_ABSOLUTE_TIME, ABSOLUTE_TIME_LOCAL, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_hf_chat_dummy_date, \
		{ "Dummy conversation date", "gg.packet.chat.dummy_date", \
		FT_ABSOLUTE_TIME, ABSOLUTE_TIME_LOCAL, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_hf_chat_unknown, \
		{ "Unknown value", "gg.packet.chat_unknown", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_hf_chat_version, \
		{ "Conversation version", "gg.packet.chat.version", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_hf_chat_name_len, \
		{ "Conversation name length", "gg.packet.chat.name.length", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_hf_chat_name, \
		{ "Conversation name", "gg.packet.chat.name", \
		FT_STRING, BASE_NONE, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_hf_chat_participants_count, \
		{ "Participants count", "gg.packet.chat.participants_count", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_hf_chat_issuer, \
		{ "issuer identifier", "gg.packet.chat.issuer", \
		FT_STRING, BASE_NONE, \
		NULL, 0, \
		NULL, HFILL } \
	}, \

void gg_dissect_chat_info(tvbuff_t *tvb, proto_tree *tree);
void gg_dissect_chat_info_update(tvbuff_t *tvb, proto_tree *tree);
void gg_dissect_chat_leave(tvbuff_t *tvb, proto_tree *tree);
void gg_dissect_chat_new(tvbuff_t *tvb, proto_tree *tree);
void gg_dissect_chat_created(tvbuff_t *tvb, proto_tree *tree);
void gg_dissect_chat_invite(tvbuff_t *tvb, proto_tree *tree);
void gg_dissect_chat_invite_ack(tvbuff_t *tvb, proto_tree *tree);

#endif /* _GG_DISSECT_NEW_H */
