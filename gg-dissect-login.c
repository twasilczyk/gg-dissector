#include "gg-dissect-login.h"

#include "gg-bitfield.h"

int gg_dissect_login_hf_welcome_seed = -1;

int gg_dissect_login_hf_login80_uin = -1;
int gg_dissect_login_hf_login80_language = -1;
int gg_dissect_login_hf_login80_hash_type = -1;
int gg_dissect_login_hf_login80_hash = -1;
int gg_dissect_login_hf_login80_status = -1;
int gg_dissect_login_hf_login80_statusflags = -1;
int gg_dissect_login_hf_login80_flags = -1;
int gg_dissect_login_hf_login80_flags_audio = -1;
int gg_dissect_login_hf_login80_flags_video = -1;
int gg_dissect_login_hf_login80_flags_mobile = -1;
int gg_dissect_login_hf_login80_flags_spam = -1;
int gg_dissect_login_hf_login80_features = -1;
int gg_dissect_login_hf_login80_local_ip = -1;
int gg_dissect_login_hf_login80_local_port = -1;
int gg_dissect_login_hf_login80_external_ip = -1;
int gg_dissect_login_hf_login80_external_port = -1;
int gg_dissect_login_hf_login80_image_size = -1;
int gg_dissect_login_hf_login80_version_len = -1;
int gg_dissect_login_hf_login80_version = -1;
int gg_dissect_login_hf_login80_description_size = -1;
int gg_dissect_login_hf_login80_description = -1;

int gg_dissect_login_hf_login105_unknown = -1;
int gg_dissect_login_hf_login105_fragment = -1;
int gg_dissect_login_hf_login105_fragment_type = -1;
int gg_dissect_login_hf_login105_language_len = -1;
int gg_dissect_login_hf_login105_tuin_len = -1;
int gg_dissect_login_hf_login105_tuin = -1;
int gg_dissect_login_hf_login105_version_len = -1;
int gg_dissect_login_hf_login105_description_size = -1;
int gg_dissect_login_hf_login105_userdata_len = -1;
int gg_dissect_login_hf_login105_userdata = -1;
int gg_dissect_login_hf_login105_hash_len = -1;

const value_string gg_dissect_login_hf_login80_hash_type_names[] = {
	{ 0x01, "GG_LOGIN_HASH_GG32" },
	{ 0x02, "GG_LOGIN_HASH_SHA1" },

	{0, NULL}
};

extern void gg_dissect_login_welcome(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, gg_dissect_login_hf_welcome_seed, tvb, 0, 4,
		ENC_LITTLE_ENDIAN);
}

extern void gg_dissect_login_login80(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 0;
	int version_len, description_size;
	
	proto_tree_add_item(tree, gg_dissect_login_hf_login80_uin, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;

	proto_tree_add_item(tree, gg_dissect_login_hf_login80_language, tvb,
		offset, 2, FALSE);
	offset += 2;

	proto_tree_add_item(tree, gg_dissect_login_hf_login80_hash_type, tvb,
		offset, 1, FALSE);
	offset += 1;
	
	proto_tree_add_item(tree, gg_dissect_login_hf_login80_hash, tvb,
		offset, 64, FALSE);
	offset += 64;
	
	proto_tree_add_item(tree, gg_dissect_login_hf_login80_status, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	offset += 1;
	gg_bitfield_statusflags_add(tree, tvb, offset,
		gg_dissect_login_hf_login80_statusflags);
	offset += 3;

	gg_bitfield_connectionflags_add(tree, tvb, offset,
		gg_dissect_login_hf_login80_flags);
	offset += 4;

	gg_bitfield_features_add(tree, tvb, offset,
		gg_dissect_login_hf_login80_features);
	offset += 4;

	proto_tree_add_item(tree, gg_dissect_login_hf_login80_local_ip, tvb,
		offset, 4, ENC_BIG_ENDIAN);
	offset += 4;

	proto_tree_add_item(tree, gg_dissect_login_hf_login80_local_port, tvb,
		offset, 2, ENC_LITTLE_ENDIAN);
	offset += 2;

	proto_tree_add_item(tree, gg_dissect_login_hf_login80_external_ip, tvb,
		offset, 4, ENC_BIG_ENDIAN);
	offset += 4;

	proto_tree_add_item(tree, gg_dissect_login_hf_login80_external_port, tvb,
		offset, 2, ENC_LITTLE_ENDIAN);
	offset += 2;

	proto_tree_add_item(tree, gg_dissect_login_hf_login80_image_size, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	offset += 1;
	
	/* unknown1 */
	offset += 1;

	proto_tree_add_item(tree, gg_dissect_login_hf_login80_version_len, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	version_len = tvb_get_letohl(tvb, offset);
	offset += 4;

	proto_tree_add_item(tree, gg_dissect_login_hf_login80_version, tvb,
		offset, version_len, FALSE);
	offset += version_len;

	proto_tree_add_item(tree, gg_dissect_login_hf_login80_description_size, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	description_size = tvb_get_letohl(tvb, offset);
	offset += 4;

	if (description_size > 0)
	{
		proto_tree_add_item(tree,
			gg_dissect_login_hf_login80_description, tvb,
			offset, description_size, FALSE);
		offset += description_size;
	}
}

static void gg_dissect_login_login105_0a(tvbuff_t *tvb, proto_tree *tree);
static void gg_dissect_login_login105_1a(tvbuff_t *tvb, proto_tree *tree);
static void gg_dissect_login_login105_3a(tvbuff_t *tvb, proto_tree *tree);
static void gg_dissect_login_login105_4a(tvbuff_t *tvb, proto_tree *tree);
static void gg_dissect_login_login105_5a(tvbuff_t *tvb, proto_tree *tree);
static int gg_dissect_login_login105_fragment_len(tvbuff_t *tvb, int offset);

extern void gg_dissect_login_login105(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 0;
	
	while (TRUE)
	{
		int fragment_type, fragment_len;
		tvbuff_t *fragment_tvb;
		proto_item *fragment_ti;
		proto_tree *fragment_tree;
		
		fragment_len = gg_dissect_login_login105_fragment_len(tvb, offset);
		if (fragment_len == 0)
			break;
		fragment_type = tvb_get_guint8(tvb, offset);

		fragment_tvb = tvb_new_subset(tvb, offset, fragment_len, fragment_len);
		fragment_ti = proto_tree_add_bytes_format_value(tree,
			gg_dissect_login_hf_login105_fragment, fragment_tvb,
			0, -1, NULL, "0x%02x", fragment_type);
		fragment_tree = proto_item_add_subtree(fragment_ti, ett_gg);
		
		proto_tree_add_item(fragment_tree, gg_dissect_login_hf_login105_fragment_type, fragment_tvb,
			0, 1, FALSE);
		fragment_type = tvb_get_guint8(tvb, offset);
		
		if (fragment_type == 0x0A)
			gg_dissect_login_login105_0a(fragment_tvb, fragment_tree);
		else if (fragment_type == 0x1A)
			gg_dissect_login_login105_1a(fragment_tvb, fragment_tree);
		else if (fragment_type == 0x3A)
			gg_dissect_login_login105_3a(fragment_tvb, fragment_tree);
		else if (fragment_type == 0x4A)
			gg_dissect_login_login105_4a(fragment_tvb, fragment_tree);
		else if (fragment_type == 0x5A)
			gg_dissect_login_login105_5a(fragment_tvb, fragment_tree);

		offset += fragment_len;
	}

	/* 60:ff:01:68:64 gg10.5 */
	/* 60:ff:01:68:64:75:7f:00:00:00:78:00:88:01:00 gg11 */
	proto_tree_add_item(tree, gg_dissect_login_hf_login105_unknown, tvb,
		offset, -1, FALSE);
}

int gg_dissect_login_login105_fragment_len(tvbuff_t *tvb, int offset)
{
	int fragment;
	int original_offset = offset;
	
	fragment = tvb_get_guint8(tvb, offset);
	offset++;
	
	if (fragment == 0x0A)
	{
		int language_len, tuin_len;
		
		language_len = tvb_get_guint8(tvb, offset);
		offset += 1 + language_len + 3;
		tuin_len = tvb_get_guint8(tvb, offset);
		offset += 1 + tuin_len;
	}
	else if (fragment == 0x1A)
	{
		int hash_len;
		
		hash_len = tvb_get_guint8(tvb, offset);
		offset += 1 + hash_len + 12;
	}
	else if (fragment == 0x3A)
	{
		int version_len;
		
		version_len = tvb_get_guint8(tvb, offset);
		offset += 1 + version_len + 5;
	}
	else if (fragment == 0x4A)
	{
		int description_len;
		
		description_len = tvb_get_guint8(tvb, offset);
		offset += 1 + description_len + 6;
	}
	else if (fragment == 0x5A)
	{
		int userdata_len;
		
		userdata_len = tvb_get_guint8(tvb, offset);
		offset += 1 + userdata_len;
	}
	else
		return 0;
	
	return offset - original_offset;
}

void gg_dissect_login_login105_0a(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 1;
	int tuin_len, language_len;
	
	proto_tree_add_item(tree, gg_dissect_login_hf_login105_language_len, tvb,
		offset, 1, FALSE);
	language_len = tvb_get_guint8(tvb, offset);
	offset += 1;
	proto_tree_add_item(tree, gg_dissect_login_hf_login80_language, tvb,
		offset, language_len, FALSE);
	offset += language_len;
	
	/* 12 0a 00: winxp virtualbox 10.5 */
	proto_tree_add_item(tree, gg_dissect_login_hf_login105_unknown, tvb,
		offset, 3, FALSE);
	offset += 3;
	
	proto_tree_add_item(tree, gg_dissect_login_hf_login105_tuin_len, tvb,
		offset, 1, FALSE);
	tuin_len = tvb_get_guint8(tvb, offset);
	offset += 1;

	proto_tree_add_item(tree, gg_dissect_login_hf_login105_tuin, tvb,
		offset, tuin_len, FALSE);
	offset += tuin_len;
}

void gg_dissect_login_login105_1a(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 1;
	int hash_len;
	int tmp;

	proto_tree_add_item(tree, gg_dissect_login_hf_login105_hash_len, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	hash_len = tvb_get_guint8(tvb, offset);
	offset += 1;
	proto_tree_add_item(tree, gg_dissect_login_hf_login80_hash, tvb,
		offset, hash_len, FALSE);
	offset += hash_len;
	
	/* 20:02:2d */
	proto_tree_add_item(tree, gg_dissect_login_hf_login105_unknown, tvb,
		offset, 3, FALSE);
	offset += 3;

	tmp = tvb_get_guint8(tvb, offset);
	proto_tree_add_bytes_format(tree,
			gg_dissect_login_hf_login105_unknown, tvb,
			offset, 1, NULL, "flags format (?): 0x%02x", tmp);
	offset += 1;
	
	if (tmp == 0x37) /* gg 10.5 */
	{
		/*
		   0xC7 - ?
		   0x20 - informuj rozmówców o pisaniu
		*/
		tmp = tvb_get_guint8(tvb, offset);
		proto_tree_add_bytes_format(tree,
				gg_dissect_login_hf_login105_unknown, tvb,
				offset, 1, NULL, "privacy options (?): 0x%02x", tmp);
		offset += 1;
	
		/* 02:00:35 win7 lapek; winxp vbox */
		proto_tree_add_item(tree, gg_dissect_login_hf_login105_unknown, tvb,
			offset, 3, FALSE);
		offset += 3;

		gg_bitfield_connectionflags_add(tree, tvb, offset,
			gg_dissect_login_hf_login80_flags);
		offset += 4;
	}
	else if (tmp == 0x77) /* gg 11.0 */
	{
		/* ff:ae:01:35:14 win7 lapek; winxp vbox */
		proto_tree_add_item(tree, gg_dissect_login_hf_login105_unknown, tvb,
			offset, 5, FALSE);
		offset += 5;

		/* 0x06 - pokazuj kamerkę znajomym */
		tmp = tvb_get_guint8(tvb, offset);
		proto_tree_add_bytes_format(tree,
				gg_dissect_login_hf_login105_unknown, tvb,
				offset, 1, NULL, "privacy options (?): 0x%02x", tmp);
		offset += 1;

		/* 03 00 win7 lapek; winxp vbox */
		proto_tree_add_item(tree, gg_dissect_login_hf_login105_unknown, tvb,
			offset, 2, FALSE);
		offset += 2;
	}
	else
	{
		proto_tree_add_item(tree, gg_dissect_login_hf_login105_unknown, tvb,
			offset, -1, FALSE);
	}
}

void gg_dissect_login_login105_3a(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 1;
	int version_len;
	
	proto_tree_add_item(tree, gg_dissect_login_hf_login105_version_len, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	version_len = tvb_get_guint8(tvb, offset);
	offset += 1;
	proto_tree_add_item(tree, gg_dissect_login_hf_login80_version, tvb,
		offset, version_len, FALSE);
	offset += version_len;
	
	/* 45 | raz miałem 4E */
	proto_tree_add_item(tree, gg_dissect_login_hf_login105_unknown, tvb,
		offset, 1, FALSE);
	offset += 1;
	
	proto_tree_add_item(tree, gg_dissect_login_hf_login80_status, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	offset += 1;
	gg_bitfield_statusflags_add(tree, tvb, offset,
		gg_dissect_login_hf_login80_statusflags);
	offset += 3;
}

void gg_dissect_login_login105_4a(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 1;
	int description_size;
	
	proto_tree_add_item(tree, gg_dissect_login_hf_login105_description_size, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	description_size = tvb_get_guint8(tvb, offset);
	offset += 1;
	if (description_size > 0)
	{
		proto_tree_add_item(tree,
			gg_dissect_login_hf_login80_description, tvb,
			offset, description_size, FALSE);
		offset += description_size;
	}
	
	/* 52:04:00:00:00:00 */
	proto_tree_add_item(tree, gg_dissect_login_hf_login105_unknown, tvb,
		offset, 6, FALSE);
	offset += 6;
}

void gg_dissect_login_login105_5a(tvbuff_t *tvb, proto_tree *tree)
{
	int offset = 1;
	int userdata_len;

	proto_tree_add_item(tree, gg_dissect_login_hf_login105_userdata_len, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	userdata_len = tvb_get_guint8(tvb, offset);
	offset += 1;
	proto_tree_add_item(tree, gg_dissect_login_hf_login105_userdata, tvb,
		offset, userdata_len, FALSE);
	offset += userdata_len;
}
