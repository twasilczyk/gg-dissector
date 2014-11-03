#include <stdio.h>

#include "gg-tvb.h"

int gg_tvb_data = -1;
int gg_tvb_byte = -1;
int gg_tvb_packed_uint = -1;

guint64 gg_tvb_read_packed_uint(tvbuff_t *tvb, gint *offset)
{
	guint64 val = 0;
	int i, val_len = 0;

	while (tvb_length_remaining(tvb, *offset + val_len) > 0)
	{
		val_len++;
		if (!(tvb_get_guint8(tvb, *offset + val_len - 1) & 0x80))
			break;
	}

	if (val_len > 9)
	{
		(*offset)++;
		fprintf(stderr, "too long\n");
		return 0;
	}

	for (i = 1; i <= val_len; i++)
	{
		guint64 old_val = val;
		val <<= 7;
		if (old_val != (val >> 7))
		{
			fprintf(stderr, "bad val\n");
			return 0;
		}
		val |= (guint8)(tvb_get_guint8(tvb, *offset + val_len - i) & ~0x80);
	}

	(*offset) += val_len;

	return val;
}

gint gg_tvb_dissect_data(tvbuff_t *tvb, gint offset, proto_tree *tree)
{
	guint8 start = offset;
	guint8 len = gg_tvb_read_packed_uint(tvb, &offset);
	offset += len;

	proto_tree_add_bytes(tree, gg_tvb_data, tvb, start + 1, offset - start - 1,
		tvb_get_ptr(tvb, start + 1, offset - start - 1));

	return offset;
}

gint gg_tvb_dissect_byte(tvbuff_t *tvb, gint offset, proto_tree *tree)
{
	proto_tree_add_item(tree, gg_tvb_byte, tvb, offset, 1, ENC_LITTLE_ENDIAN);

	return offset + 1;
}

gint gg_tvb_dissect_packed_uint(tvbuff_t *tvb, gint offset, proto_tree *tree)
{
	guint8 start = offset;
	guint64 val = gg_tvb_read_packed_uint(tvb, &offset);

	proto_tree_add_bytes_format_value(tree, gg_tvb_packed_uint, tvb, start, offset - start,
		tvb_get_ptr(tvb, start, offset - start), "%" G_GUINT64_FORMAT, val);

	return offset;
}

void gg_tvb_dissect(tvbuff_t *tvb, proto_tree *tree)
{
	gint offset = 0;

	while (tvb_length_remaining(tvb, offset) > 0)
	{
		guint8 type = tvb_get_guint8(tvb, offset++);
		if (type == 0x0a || type == 0x2a || type == 0x32 || type == 0x3a)
			offset = gg_tvb_dissect_data(tvb, offset, tree);
		else if (type == 0x10 || type == 0x08)
			offset = gg_tvb_dissect_byte(tvb, offset, tree);
		else if (type == 0x18 || type == 0x20 || type == 0x28)
			offset = gg_tvb_dissect_packed_uint(tvb, offset, tree);
		else
			break;
	}
}
