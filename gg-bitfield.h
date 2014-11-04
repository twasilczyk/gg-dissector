#ifndef _GG_BITFIELD_H
#define _GG_BITFIELD_H

#include "packet-gg.hpp"

#include <epan/packet.h>

extern gint ett_gg_bitfield_connectionflags;
extern const int * gg_bitfield_connectionflags_fields[];
extern int gg_bitfield_hf_connectionflags_audio;
extern int gg_bitfield_hf_connectionflags_video;
extern int gg_bitfield_hf_connectionflags_mobile;
extern int gg_bitfield_hf_connectionflags_spam;
extern void gg_bitfield_connectionflags_add(
	proto_tree *tree, tvbuff_t *tvb, const guint offset, const int hf_hdr);

extern gint ett_gg_bitfield_features;
extern const int * gg_bitfield_features_fields[];
extern int gg_bitfield_features_status_fmt;
extern int gg_bitfield_features_msg_fmt;
extern int gg_bitfield_features_dnd_ffc;
extern int gg_bitfield_features_image_descr;
extern int gg_bitfield_features_login_failed_fmt;
extern int gg_bitfield_features_user_data;
extern int gg_bitfield_features_msg_ack;
extern int gg_bitfield_features_typing_notification;
extern int gg_bitfield_features_multilogon;
extern const value_string gg_bitfield_features_status_fmt_names[];
extern void gg_bitfield_features_add(
	proto_tree *tree, tvbuff_t *tvb, const guint offset, const int hf_hdr);

extern gint ett_gg_bitfield_statusflags;
extern const int * gg_bitfield_statusflags_fields[];
extern int gg_bitfield_hf_statusflags_image;
extern int gg_bitfield_hf_statusflags_adapt_status;
extern int gg_bitfield_hf_statusflags_last_status;
extern int gg_bitfield_hf_statusflags_descr;
extern int gg_bitfield_hf_statusflags_friends;
extern void gg_bitfield_statusflags_add(
	proto_tree *tree, tvbuff_t *tvb, const guint offset, const int hf_hdr);

#define ETT_GG_BITFIELD \
	&ett_gg_bitfield_connectionflags, \
	&ett_gg_bitfield_features, \
	&ett_gg_bitfield_statusflags, \

#define GG_BITFIELD_HF \
	{ &gg_bitfield_hf_connectionflags_audio, \
		{ "audio", "gg.packet.common.connectionflags.audio", \
		FT_BOOLEAN, 32, \
		TFS(&tfs_set_notset), 0x00000001, \
		"client accepts audio connections (probably)", HFILL } \
	}, \
	{ &gg_bitfield_hf_connectionflags_video, \
		{ "video", "gg.packet.common.connectionflags.video", \
		FT_BOOLEAN, 32, \
		TFS(&tfs_set_notset), 0x00000002, \
		"client accepts video connections", HFILL } \
	}, \
	{ &gg_bitfield_hf_connectionflags_mobile, \
		{ "mobile", "gg.packet.common.connectionflags.mobile", \
		FT_BOOLEAN, 32, \
		TFS(&tfs_set_notset), 0x00100000, \
		"Mobile client", HFILL } \
	}, \
	{ &gg_bitfield_hf_connectionflags_spam, \
		{ "accepts links from strangers", "gg.packet.common.connectionflags.spam", \
		FT_BOOLEAN, 32, \
		TFS(&tfs_set_notset), 0x00800000, \
		"Client accepts links sent from users, which are not on their buddy list", HFILL } \
	}, \
	\
	{ &gg_bitfield_features_status_fmt, \
		{ "status format", "gg.packet.common.features.status_fmt", \
		FT_UINT32, BASE_HEX, \
		VALS(gg_bitfield_features_status_fmt_names), \
		0x00000005, \
		"type of supported GG_STATUS* and GG_NOTIFY_REPLY* packets", HFILL } \
	}, \
	{ &gg_bitfield_features_msg_fmt, \
		{ "GG8.0 messages", "gg.packet.common.features.msg_fmt", \
		FT_BOOLEAN, 32, \
		TFS(&tfs_set_notset), 0x00000002, \
		"client supports GG_RECV_MSG80 packets", HFILL } \
	}, \
	{ &gg_bitfield_features_dnd_ffc, \
		{ "DND and FFC statuses", \
		"gg.packet.common.features.dnd_ffc", \
		FT_BOOLEAN, 32, \
		TFS(&tfs_set_notset), 0x00000010, \
		"supports \"do not disturb\" and \"free for chat\" statuses", HFILL } \
	}, \
	{ &gg_bitfield_features_image_descr, \
		{ "graphical status", \
		"gg.packet.common.features.image_descr", \
		FT_BOOLEAN, 32, \
		TFS(&tfs_set_notset), 0x00000020, \
		"and GG_STATUS_DESCR_MASK", HFILL } \
	}, \
	{ &gg_bitfield_features_login_failed_fmt, \
		{ "GG_LOGIN80_FAILED", \
		"gg.packet.common.features.login_failed_fmt", \
		FT_BOOLEAN, 32, \
		TFS(&tfs_set_notset), 0x00000040, \
		NULL, HFILL } \
	}, \
	{ &gg_bitfield_features_user_data, \
		{ "user data", \
		"gg.packet.common.features.user_data", \
		FT_BOOLEAN, 32, \
		TFS(&tfs_set_notset), 0x00000200, \
		"supports additional buddy list information", HFILL } \
	}, \
	{ &gg_bitfield_features_msg_ack, \
		{ "message ACK", \
		"gg.packet.common.features.msg_ack", \
		FT_BOOLEAN, 32, \
		TFS(&tfs_set_notset), 0x00000400, \
		"supports message acknowledgment", HFILL } \
	}, \
	{ &gg_bitfield_features_typing_notification, \
		{ "typing notifications", \
		"gg.packet.common.features.typing_notification", \
		FT_BOOLEAN, 32, \
		TFS(&tfs_set_notset), 0x00002000, \
		NULL, HFILL } \
	}, \
	{ &gg_bitfield_features_multilogon, \
		{ "multilogon", \
		"gg.packet.common.features.multilogon", \
		FT_BOOLEAN, 32, \
		TFS(&tfs_set_notset), 0x00004000, \
		NULL, HFILL } \
	}, \
	\
	{ &gg_bitfield_hf_statusflags_image, \
		{ "image", \
		"gg.packet.common.statusflags.image", \
		FT_BOOLEAN, 24, \
		TFS(&tfs_set_notset), 0x000001, \
		"image status description is set", HFILL } \
	}, \
	{ &gg_bitfield_hf_statusflags_adapt_status, \
		{ "adaptive status", \
		"gg.packet.common.statusflags.adapt_status", \
		FT_BOOLEAN, 24, \
		TFS(&tfs_set_notset), 0x000004, \
		"when making new connection - if there is another connection with status set, ignore this one", HFILL } \
	}, \
	{ &gg_bitfield_hf_statusflags_last_status, \
		{ "use last status (?)", \
		"gg.packet.common.statusflags.last_status", \
		FT_BOOLEAN, 24, \
		TFS(&tfs_set_notset), 0x000020, \
		"when making new connection - use previously set status", HFILL } \
	}, \
	{ &gg_bitfield_hf_statusflags_descr, \
		{ "description", \
		"gg.packet.common.statusflags.descr", \
		FT_BOOLEAN, 24, \
		TFS(&tfs_set_notset), 0x000040, \
		"description is set", HFILL } \
	}, \
	{ &gg_bitfield_hf_statusflags_friends, \
		{ "friends only", \
		"gg.packet.common.statusflags.friends", \
		FT_BOOLEAN, 24, \
		TFS(&tfs_set_notset), 0x000080, \
		"status is visible for friends only", HFILL } \
	}, \

#endif
