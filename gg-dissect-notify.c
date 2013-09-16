#include "gg-dissect-notify.h"

#include "gg-bitfield.h"

#include <glib.h>
#include <glib/gprintf.h>

int gg_dissect_notify_hf_uin = -1;
int gg_dissect_notify_hf_status = -1;
int gg_dissect_notify_hf_statusflags = -1;
int gg_dissect_notify_hf_features = -1;
int gg_dissect_notify_hf_remote_ip = -1;
int gg_dissect_notify_hf_remote_port = -1;
int gg_dissect_notify_hf_image_size = -1;
int gg_dissect_notify_hf_flags = -1;
int gg_dissect_notify_hf_description_size = -1;
int gg_dissect_notify_hf_description = -1;

gint ett_gg_dissect_notify_hf_firstlast_type = -1;
int gg_dissect_notify_hf_firstlast_record = -1;
int gg_dissect_notify_hf_firstlast_uin = -1;
int gg_dissect_notify_hf_firstlast_type = -1;
int gg_dissect_notify_hf_firstlast_type_buddy = -1;
int gg_dissect_notify_hf_firstlast_type_friend = -1;
int gg_dissect_notify_hf_firstlast_type_blocked = -1;
const int * gg_dissect_notify_hf_firstlast_type_fields[] = {
	&gg_dissect_notify_hf_firstlast_type_buddy,
	&gg_dissect_notify_hf_firstlast_type_friend,
	&gg_dissect_notify_hf_firstlast_type_blocked,
	NULL
};

int gg_dissect_notify_hf_userdata_type = -1;
int gg_dissect_notify_hf_userdata_usernum = -1;
int gg_dissect_notify_hf_userdata_user = -1;
int gg_dissect_notify_hf_userdata_uin = -1;
int gg_dissect_notify_hf_userdata_attrnum = -1;
int gg_dissect_notify_hf_userdata_attr = -1;
int gg_dissect_notify_hf_userdata_attr_name_size = -1;
int gg_dissect_notify_hf_userdata_attr_name = -1;
int gg_dissect_notify_hf_userdata_attr_type = -1;
int gg_dissect_notify_hf_userdata_attr_value_size = -1;
int gg_dissect_notify_hf_userdata_attr_value = -1;

const value_string gg_dissect_notify_status_names[] = {
	{ 0x01, "GG_STATUS_NOT_AVAIL" },
	{ 0x15, "GG_STATUS_NOT_AVAIL_DESCR" },
	{ 0x17, "GG_STATUS_FFC" },
	{ 0x18, "GG_STATUS_FFC_DESCR" },
	{ 0x02, "GG_STATUS_AVAIL" },
	{ 0x04, "GG_STATUS_AVAIL_DESCR" },
	{ 0x03, "GG_STATUS_BUSY" },
	{ 0x05, "GG_STATUS_BUSY_DESCR" },
	{ 0x21, "GG_STATUS_DND" },
	{ 0x22, "GG_STATUS_DND_DESCR" },
	{ 0x14, "GG_STATUS_INVISIBLE" },
	{ 0x16, "GG_STATUS_INVISIBLE_DESCR" },
	{ 0x06, "GG_STATUS_BLOCKED" },
	
	{ 0x20, "GG_STATUS_GG_PLUS" },
	{ 0x23, "GG_STATUS_NOT_SET" },

	{ 0, NULL }
};

static void gg_dissect_notify_record(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 0;
	int description_size;
	
	proto_tree_add_item(tree, gg_dissect_notify_hf_uin, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;
	
	proto_tree_add_item(tree, gg_dissect_notify_hf_status, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	offset += 1;
	gg_bitfield_statusflags_add(tree, tvb, offset,
		gg_dissect_notify_hf_statusflags);
	offset += 3;
	
	gg_bitfield_features_add(tree, tvb, offset,
		gg_dissect_notify_hf_features);
	offset += 4;

	proto_tree_add_item(tree, gg_dissect_notify_hf_remote_ip, tvb,
		offset, 4, ENC_BIG_ENDIAN);
	offset += 4;
	
	proto_tree_add_item(tree, gg_dissect_notify_hf_remote_port, tvb,
		offset, 2, ENC_LITTLE_ENDIAN);
	offset += 2;
	
	proto_tree_add_item(tree, gg_dissect_notify_hf_image_size, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	offset += 1;
	
	/* unknown1 */
	offset += 1;

	gg_bitfield_connectionflags_add(tree, tvb, offset,
		gg_dissect_notify_hf_flags);
	offset += 4;
	
	proto_tree_add_item(tree, gg_dissect_notify_hf_description_size, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	description_size = tvb_get_letohl(tvb, offset);
	offset += 4;
	
	if (description_size > 0)
	{
		proto_tree_add_item(tree, gg_dissect_notify_hf_description, tvb,
			offset, description_size, FALSE);
		offset += description_size;
	}
}

extern void gg_dissect_notify_status80(tvbuff_t *tvb, proto_tree *tree)
{
	gg_dissect_notify_record(tvb, tree);
}

extern void gg_dissect_notify_reply80(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 0;
	const int length = tvb_length(tvb);
	
	while (offset < length)
	{
		const int size_offset = 5 * sizeof(int) + 1 * sizeof(short) + 2 * sizeof(char);
		const int statusDescr_len = tvb_get_letohl(tvb, offset + size_offset);
		const int record_size = statusDescr_len + size_offset + 4;
		tvbuff_t *record_tvb = tvb_new_subset(tvb, offset, record_size, record_size);
		proto_item *record_ti;
		proto_tree *record_tree;

		const int uin = tvb_get_letohl(record_tvb, 0);
		const gchar *status = val_to_str_const(
			tvb_get_guint8(record_tvb, 4),
			gg_dissect_notify_status_names, "unknown");
		gchar *statusDescr;
		
		if (statusDescr_len > 0)
			statusDescr = g_strdup_printf(" (%s)",
				tvb_format_text(record_tvb, size_offset + 4,
					statusDescr_len));
		else
			statusDescr = g_strdup("");

		record_ti = proto_tree_add_bytes_format(tree,
			gg_dissect_notify_hf_firstlast_record, record_tvb,
			0, -1, NULL, "status for %d: %s%s", uin, status, statusDescr);
		record_tree = proto_item_add_subtree(record_ti, ett_gg);
		
		g_free(statusDescr);
		
		gg_dissect_notify_record(record_tvb, record_tree);
		offset += record_size;
	}
}

extern void gg_dissect_notify_firstlast(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 0;
	proto_item *record_ti;
	tvbuff_t *record_tvb;
	proto_tree *record_tree;
	const int length = tvb_length(tvb);

	while (offset < length)
	{
		int uin;
		char type;
		char *str_buddy;

		record_tvb = tvb_new_subset(tvb, offset, 5, 5);
		
		uin = tvb_get_letohl(record_tvb, 0);
		type = tvb_get_guint8(record_tvb, 4);
		if (type == 0x04)
			str_buddy = "blocked";
		else if (type == (0x02 | 0x01))
			str_buddy = "friend";
		else if (type == 0x01)
			str_buddy = "buddy";
		else
			str_buddy = "custom user";
	
		record_ti = proto_tree_add_bytes_format(tree,
			gg_dissect_notify_hf_firstlast_record, record_tvb,
			0, -1, NULL, "%s: %d", str_buddy, uin);
		record_tree = proto_item_add_subtree(record_ti, ett_gg);
		offset += 5;
	
		proto_tree_add_item(record_tree, gg_dissect_notify_hf_firstlast_uin, record_tvb,
			0, 4, ENC_LITTLE_ENDIAN);
	
		proto_tree_add_bitmask(record_tree, record_tvb, 4,
			gg_dissect_notify_hf_firstlast_type,
			ett_gg_dissect_notify_hf_firstlast_type,
			gg_dissect_notify_hf_firstlast_type_fields,
			FALSE);
	}
}

extern void gg_dissect_notify_new_status80(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 0;
	int description_size;
	
	proto_tree_add_item(tree, gg_dissect_notify_hf_status, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	offset += 1;
	gg_bitfield_statusflags_add(tree, tvb, offset,
		gg_dissect_notify_hf_statusflags);
	offset += 3;
	
	gg_bitfield_connectionflags_add(tree, tvb, offset,
		gg_dissect_notify_hf_flags);
	offset += 4;

	proto_tree_add_item(tree, gg_dissect_notify_hf_description_size, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	description_size = tvb_get_letohl(tvb, offset);
	offset += 4;
	
	if (description_size > 0)
	{
		proto_tree_add_item(tree, gg_dissect_notify_hf_description, tvb,
			offset, description_size, FALSE);
		offset += description_size;
	}
}

extern void gg_dissect_notify_user_data(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 0;
	int usernum;
	
	proto_tree_add_item(tree, gg_dissect_notify_hf_userdata_type, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;
	
	usernum = tvb_get_letohl(tvb, offset);
	proto_tree_add_item(tree, gg_dissect_notify_hf_userdata_usernum, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;
	
	while (usernum--)
	{
		int uin = tvb_get_letohl(tvb, offset);
		int attrnum = tvb_get_letohl(tvb, offset + 4);
		int tmpoffset = offset + 8, user_size = 8;
		int i, user_offset = 0;
		proto_item *user_ti;
		proto_tree *user_tree;
		tvbuff_t *user_tvb;
		gchar *attrnames = g_strdup("");
		
		for (i = 0; i < attrnum; i++)
		{
			int name_size = tvb_get_letohl(tvb, tmpoffset);
			int value_size = tvb_get_letohl(tvb, tmpoffset + 8 + name_size);
			int attr_size = 3 * sizeof(int) + name_size + value_size;
			gchar *tmp;
			
			tmp = g_strjoin((i == 0) ? "" : ", ", attrnames, tvb_format_text(tvb, tmpoffset + 4, name_size), NULL);
			g_free(attrnames);
			attrnames = tmp;

			tmpoffset += attr_size;
			user_size += attr_size;
		}
		
		user_tvb = tvb_new_subset(tvb, offset, user_size, user_size);
		offset += user_size;
		
		user_ti = proto_tree_add_bytes_format(
			tree, gg_dissect_notify_hf_userdata_user, user_tvb,
			0, -1, NULL, "user %d: %s", uin, attrnames);
		user_tree = proto_item_add_subtree(user_ti, ett_gg);
		
		proto_tree_add_item(user_tree, gg_dissect_notify_hf_userdata_uin, user_tvb,
			user_offset, 4, ENC_LITTLE_ENDIAN);
		user_offset += 4;
		
		proto_tree_add_item(user_tree, gg_dissect_notify_hf_userdata_attrnum, user_tvb,
			user_offset, 4, ENC_LITTLE_ENDIAN);
		user_offset += 4;
		
		while (attrnum--)
		{
			proto_item *attr_ti;
			proto_tree *attr_tree;
			int name_size = tvb_get_letohl(user_tvb, user_offset);
			int value_size = tvb_get_letohl(user_tvb, user_offset + 8 + name_size);
			tvbuff_t *attr_tvb;
			int attr_offset = 0;
			int attr_size = 3 * sizeof(int) + name_size + value_size;
			
			attr_tvb = tvb_new_subset(user_tvb, user_offset, attr_size, attr_size);
			user_offset += attr_size;
			
			attr_ti = proto_tree_add_bytes_format(
				user_tree, gg_dissect_notify_hf_userdata_attr, attr_tvb,
				0, -1, NULL, "%s=%s",
				tvb_format_text(attr_tvb, 4, name_size),
				tvb_format_text(attr_tvb, 4*3 + name_size, value_size));
			attr_tree = proto_item_add_subtree(attr_ti, ett_gg);
			
			proto_tree_add_item(attr_tree, gg_dissect_notify_hf_userdata_attr_name_size, attr_tvb,
				attr_offset, 4, ENC_LITTLE_ENDIAN);
			attr_offset += 4;
			
			proto_tree_add_item(attr_tree, gg_dissect_notify_hf_userdata_attr_name, attr_tvb,
				attr_offset, name_size, FALSE);
			attr_offset += name_size;
			
			proto_tree_add_item(attr_tree, gg_dissect_notify_hf_userdata_attr_type, attr_tvb,
				attr_offset, 4, ENC_LITTLE_ENDIAN);
			attr_offset += 4;

			proto_tree_add_item(attr_tree, gg_dissect_notify_hf_userdata_attr_value_size, attr_tvb,
				attr_offset, 4, ENC_LITTLE_ENDIAN);
			attr_offset += 4;
			
			proto_tree_add_item(attr_tree, gg_dissect_notify_hf_userdata_attr_value, attr_tvb,
				attr_offset, value_size, FALSE);
			attr_offset += value_size;
		}
	}
}
