#include "gg-bitfield.h"

gint ett_gg_bitfield_connectionflags = -1;
int gg_bitfield_hf_connectionflags_audio = -1;
int gg_bitfield_hf_connectionflags_video = -1;
int gg_bitfield_hf_connectionflags_mobile = -1;
int gg_bitfield_hf_connectionflags_spam = -1;
const int * gg_bitfield_connectionflags_fields[] = {
	&gg_bitfield_hf_connectionflags_audio,
	&gg_bitfield_hf_connectionflags_video,
	&gg_bitfield_hf_connectionflags_mobile,
	&gg_bitfield_hf_connectionflags_spam,
	NULL
};
extern void gg_bitfield_connectionflags_add(proto_tree *tree, tvbuff_t *tvb,
	const guint offset, const int hf_hdr)
{
	proto_tree_add_bitmask(tree, tvb, offset,
		hf_hdr,
		ett_gg_bitfield_connectionflags,
		gg_bitfield_connectionflags_fields,
		ENC_LITTLE_ENDIAN);
}

gint ett_gg_bitfield_features = -1;
int gg_bitfield_features_status_fmt = -1;
int gg_bitfield_features_msg_fmt = -1;
int gg_bitfield_features_dnd_ffc = -1;
int gg_bitfield_features_image_descr = -1;
int gg_bitfield_features_login_failed_fmt = -1;
int gg_bitfield_features_user_data = -1;
int gg_bitfield_features_msg_ack = -1;
int gg_bitfield_features_typing_notification = -1;
int gg_bitfield_features_multilogon = -1;
const int * gg_bitfield_features_fields[] = {
	&gg_bitfield_features_status_fmt,
	&gg_bitfield_features_msg_fmt,
	&gg_bitfield_features_dnd_ffc,
	&gg_bitfield_features_image_descr,
	&gg_bitfield_features_login_failed_fmt,
	&gg_bitfield_features_user_data,
	&gg_bitfield_features_msg_ack,
	&gg_bitfield_features_typing_notification,
	&gg_bitfield_features_multilogon,
	NULL
};
const value_string gg_bitfield_features_status_fmt_names[] = {
	{ 0x00, "GG_STATUS77" },
	{ 0x01, "GG_STATUS80BETA" },
	{ 0x05, "GG_STATUS80" },

	{ 0, NULL }
};
extern void gg_bitfield_features_add(proto_tree *tree, tvbuff_t *tvb,
	const guint offset, const int hf_hdr)
{
	proto_tree_add_bitmask(tree, tvb, offset,
		hf_hdr,
		ett_gg_bitfield_features,
		gg_bitfield_features_fields,
		ENC_LITTLE_ENDIAN);
}

gint ett_gg_bitfield_statusflags = -1;
int gg_bitfield_hf_statusflags_image = -1;
int gg_bitfield_hf_statusflags_adapt_status = -1;
int gg_bitfield_hf_statusflags_last_status = -1;
int gg_bitfield_hf_statusflags_descr = -1;
int gg_bitfield_hf_statusflags_friends = -1;
const int * gg_bitfield_statusflags_fields[] = {
	&gg_bitfield_hf_statusflags_image,
	&gg_bitfield_hf_statusflags_adapt_status,
	&gg_bitfield_hf_statusflags_last_status,
	&gg_bitfield_hf_statusflags_descr,
	&gg_bitfield_hf_statusflags_friends,
	NULL
};
extern void gg_bitfield_statusflags_add(proto_tree *tree, tvbuff_t *tvb,
	const guint offset, const int hf_hdr)
{
	proto_tree_add_bitmask(tree, tvb, offset,
		hf_hdr,
		ett_gg_bitfield_statusflags,
		gg_bitfield_statusflags_fields,
		ENC_LITTLE_ENDIAN);
}
