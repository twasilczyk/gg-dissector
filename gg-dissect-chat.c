#include "gg-dissect-new.h"

#include <stdio.h>

int gg_dissect_hf_chat_id = -1;
int gg_dissect_hf_chat_start = -1;
int gg_dissect_hf_chat_dummy_date = -1;
int gg_dissect_hf_chat_unknown = -1;
int gg_dissect_hf_chat_version = -1;
int gg_dissect_hf_chat_name_len = -1;
int gg_dissect_hf_chat_name = -1;
int gg_dissect_hf_chat_participants_count = -1;
int gg_dissect_hf_chat_issuer = -1;

static int chat_unknown_int32(tvbuff_t *tvb, proto_tree *tree, int offset)
{
	proto_tree_add_item(tree, gg_dissect_hf_chat_unknown, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	return offset + 4;
}

void gg_dissect_chat_info(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 0;
	unsigned int chat_id;
	unsigned int magic1;
	int chat_name_len;
	int chat_participants;
	int i;

	chat_id = tvb_get_letohl(tvb, offset);
	if (chat_id == 0)
		return;
	
	proto_tree_add_item(tree, gg_dissect_hf_chat_id, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;

	proto_tree_add_item(tree, gg_dissect_hf_chat_start, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;

	/* 0 */
	offset = chat_unknown_int32(tvb, tree, offset);

	proto_tree_add_item(tree, gg_dissect_hf_chat_version, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;
	
	/* 0 or 1 */
	magic1 = tvb_get_letohl(tvb, offset);
	offset = chat_unknown_int32(tvb, tree, offset);
	
	if (magic1 == 1)
	{
		chat_name_len = tvb_get_letohl(tvb, offset);
		proto_tree_add_item(tree, gg_dissect_hf_chat_name_len, tvb,
			offset, 4, ENC_LITTLE_ENDIAN);
		offset += 4;

		proto_tree_add_item(tree, gg_dissect_hf_chat_name, tvb,
			offset, chat_name_len, FALSE);
		offset += chat_name_len;
		
		/* 0 */
		offset = chat_unknown_int32(tvb, tree, offset);
		
		/* 2 */
		offset = chat_unknown_int32(tvb, tree, offset);
	}
	
	chat_participants = tvb_get_letohl(tvb, offset);
	proto_tree_add_item(tree, gg_dissect_hf_chat_participants_count, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;
	
	for (i = 0; i < chat_participants; i++)
	{
		proto_tree_add_item(tree, gg_dissect_hf_uin, tvb,
			offset, 4, ENC_LITTLE_ENDIAN);
		offset += 4;
		
		/* 0x0000001e or 0x00000018 */
		offset += 4;
	}
}

void gg_dissect_chat_info_update(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 0;
	int uin_len;
	
	/* 0x0a 0a 00 */
	offset += 3;
	
	uin_len = tvb_get_guint8(tvb, offset);
	proto_tree_add_item(tree, gg_dissect_hf_uin_s_len, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	offset += 1;
	
	proto_tree_add_item(tree, gg_dissect_hf_uin_s, tvb,
		offset, uin_len, FALSE);
	offset += uin_len;
	
	/* 0x12 0a 00 */
	offset += 3;
	
	uin_len = tvb_get_guint8(tvb, offset);
	proto_tree_add_item(tree, gg_dissect_hf_uin_s_len, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	offset += 1;
	
	proto_tree_add_item(tree, gg_dissect_hf_chat_issuer, tvb,
		offset, uin_len, FALSE);
	offset += uin_len;
	
	/* 0x1d */
	offset++;
	
	offset = chat_unknown_int32(tvb, tree, offset); /* 1 - wszedł, 3 - wyszedł */
	
	/* 0x25 */
	offset++;
	
	proto_tree_add_item(tree, gg_dissect_hf_chat_dummy_date, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;
	

	/* 0x2d xx 00 00 00 30 : xx=5e - dodanie, 00 - usunięcie*/
	offset += 6;

	/* TODO: packed int */
	proto_tree_add_item(tree, gg_dissect_hf_chat_version, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	offset += 1;

	/* 0x38 xx 49 0_ 10 0_ 00 - xx: podobny do numeru wersji*/
	offset += 7;
	
	proto_tree_add_item(tree, gg_dissect_hf_chat_dummy_date, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;

	/* 0x51 */
	offset++;

	proto_tree_add_item(tree, gg_dissect_hf_chat_id, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;
	
	proto_tree_add_item(tree, gg_dissect_hf_chat_start, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;
	
	/* 0x59 0_ 10 00 00 */
	offset += 5;

	proto_tree_add_item(tree, gg_dissect_hf_chat_dummy_date, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;
}

void gg_dissect_chat_leave(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 0;

	proto_tree_add_item(tree, gg_dissect_hf_chat_id, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;

	proto_tree_add_item(tree, gg_dissect_hf_chat_start, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;

	proto_tree_add_item(tree, gg_dissect_hf_seq_out, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;
}

void gg_dissect_chat_new(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 0;

	proto_tree_add_item(tree, gg_dissect_hf_seq_out, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;
	
	/* 0x00 00 00 00 */
	offset += 4;
}

void gg_dissect_chat_created(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 0;
	
	proto_tree_add_item(tree, gg_dissect_hf_chat_id, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;
	
	proto_tree_add_item(tree, gg_dissect_hf_chat_start, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;
	
	proto_tree_add_item(tree, gg_dissect_hf_seq_out, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;
}

void gg_dissect_chat_invite(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 0;
	int chat_participants, i;
	
	proto_tree_add_item(tree, gg_dissect_hf_chat_id, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;
	
	proto_tree_add_item(tree, gg_dissect_hf_chat_start, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;

	proto_tree_add_item(tree, gg_dissect_hf_seq_out, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;

	chat_participants = tvb_get_letohl(tvb, offset);
	proto_tree_add_item(tree, gg_dissect_hf_chat_participants_count, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;
	
	for (i = 0; i < chat_participants; i++)
	{
		proto_tree_add_item(tree, gg_dissect_hf_uin, tvb,
			offset, 4, ENC_LITTLE_ENDIAN);
		offset += 4;
		
		/* 0x0000001e */
		offset += 4;
	}
}

void gg_dissect_chat_invite_ack(tvbuff_t *tvb, proto_tree *tree)
{ // only when creating new conversation
	int offset = 0;
	
	proto_tree_add_item(tree, gg_dissect_hf_chat_id, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;
	
	proto_tree_add_item(tree, gg_dissect_hf_chat_start, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;

	proto_tree_add_item(tree, gg_dissect_hf_seq_out, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;

	/* 0x10 00 00 00  00 00 00 00 */
	offset += 8;
}
