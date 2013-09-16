#include "gg-dissect-new.h"

#include <stdio.h>

int gg_dissect_hf_uin = -1;
int gg_dissect_hf_uin_s = -1;
int gg_dissect_hf_uin_s_len = -1;
int gg_dissect_hf_seq_out = -1;

int gg_dissect_hf_imtoken_len = -1;
int gg_dissect_hf_imtoken = -1;

int gg_dissect_hf_mpa_seq = -1;
int gg_dissect_hf_mpa_data = -1;
int gg_dissect_hf_mpa_data_len = -1;

void gg_dissect_imtoken(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 0;
	int token_len;
	
	/* magic: 0x0a */
	offset += 1;
	
	proto_tree_add_item(tree, gg_dissect_hf_imtoken_len, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	token_len = tvb_get_guint8(tvb, offset);
	offset += 1;

	proto_tree_add_item(tree, gg_dissect_hf_imtoken, tvb,
		offset, token_len, FALSE);
	offset += token_len;
}

void gg_dissect_mpa_notify(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 0;
	int data_len;
	int magic;
	
	/* magic 08 02 10 */
	offset += 3;
	
	proto_tree_add_item(tree, gg_dissect_hf_mpa_seq, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	offset += 1;
	
	/* magic 1a */
	offset += 1;
	
	proto_tree_add_item(tree, gg_dissect_hf_mpa_data_len, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	data_len = tvb_get_guint8(tvb, offset);
	offset += 1;

	magic = tvb_get_guint8(tvb, offset);
	if (magic == 0x01) //TODO: size!
		offset += 1;
	
	proto_tree_add_item(tree, gg_dissect_hf_mpa_data, tvb,
		offset, data_len, FALSE);
	offset += data_len;
	
	if (tvb_length_remaining(tvb, offset) == 0)
		return;
	
	/* magic 22 */
	offset += 1;
	
	proto_tree_add_item(tree, gg_dissect_hf_mpa_data_len, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	data_len = tvb_get_guint8(tvb, offset);
	offset += 1;
	
	proto_tree_add_item(tree, gg_dissect_hf_mpa_data, tvb,
		offset, data_len, FALSE);
	offset += data_len;
	
	/* magic:
	 *  - 28 82 8c 9c 80 c0 c5 9c 89 50
	 *  - 28 81 8c a0 80 c0 c5 9c 89 50
	 *  - 28 81 8c 88 80 a0 be ab 89 50
	 *  - 28 81 8c 88 80 c0 e6 ab 89 50
	 *  - 28 83 8c 84 80 a0 c7 9c 89 50
	 *  - 28 83 8c 88 80 a0 be ab 89 50
	 */
}

void gg_dissect_mpa_ack(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 0;
	
	/* magic 08 06 10 */
	offset += 3;
	
	proto_tree_add_item(tree, gg_dissect_hf_mpa_seq, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	offset += 1;
	
	/* magic 18 01 */
	offset += 2;
}
