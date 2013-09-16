#ifndef _GG_DISSECT_NOTIFY_H
#define _GG_DISSECT_NOTIFY_H

#include "packet-gg.h"

extern int gg_dissect_notify_hf_uin;
extern int gg_dissect_notify_hf_status;
extern int gg_dissect_notify_hf_statusflags;
extern int gg_dissect_notify_hf_features;
extern int gg_dissect_notify_hf_remote_ip;
extern int gg_dissect_notify_hf_remote_port;
extern int gg_dissect_notify_hf_image_size;
extern int gg_dissect_notify_hf_flags;
extern int gg_dissect_notify_hf_description_size;
extern int gg_dissect_notify_hf_description;
extern const value_string gg_dissect_notify_status_names[];

extern int gg_dissect_notify_hf_firstlast_record;
extern int gg_dissect_notify_hf_firstlast_uin;
extern int gg_dissect_notify_hf_firstlast_type;

extern gint ett_gg_dissect_notify_hf_firstlast_type;
extern const int * gg_dissect_notify_hf_firstlast_type_fields[];
extern int gg_dissect_notify_hf_firstlast_type_buddy;
extern int gg_dissect_notify_hf_firstlast_type_friend;
extern int gg_dissect_notify_hf_firstlast_type_blocked;

extern int gg_dissect_notify_hf_userdata_type;
extern int gg_dissect_notify_hf_userdata_usernum;
extern int gg_dissect_notify_hf_userdata_user;
extern int gg_dissect_notify_hf_userdata_uin;
extern int gg_dissect_notify_hf_userdata_attrnum;
extern int gg_dissect_notify_hf_userdata_attr;
extern int gg_dissect_notify_hf_userdata_attr_name_size;
extern int gg_dissect_notify_hf_userdata_attr_name;
extern int gg_dissect_notify_hf_userdata_attr_type;
extern int gg_dissect_notify_hf_userdata_attr_value_size;
extern int gg_dissect_notify_hf_userdata_attr_value;

#define ETT_GG_DISSECT_NOTIFY \
	&ett_gg_dissect_notify_hf_firstlast_type,

#define GG_DISSECT_NOTIFY_HF \
	{ &gg_dissect_notify_hf_uin, \
		{ "user identifier", "gg.packet.notify.uin", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_notify_hf_status, \
		{ "status", "gg.packet.notify.status", \
		FT_UINT8, BASE_HEX, \
		VALS(gg_dissect_notify_status_names), 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_notify_hf_statusflags, \
		{ "status flags", "gg.packet.notify.statusflags", \
		FT_UINT24, BASE_HEX, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_notify_hf_features, \
		{ "features", "gg.packet.notify.features", \
		FT_UINT32, BASE_HEX, \
		NULL, 0, \
		"supported features", HFILL } \
	}, \
	{ &gg_dissect_notify_hf_remote_ip, \
		{ "remote ip", "gg.packet.notify.remote_ip", \
		FT_IPv4, BASE_NONE, \
		NULL, 0, \
		"remote address for direct connections", HFILL } \
	}, \
	{ &gg_dissect_notify_hf_remote_port, \
		{ "remote port", "gg.packet.notify.remote_port", \
		FT_UINT16, BASE_DEC, \
		NULL, 0, \
		"remote port for direct connections - unused", HFILL } \
	}, \
	{ &gg_dissect_notify_hf_image_size, \
		{ "maximum image size", "gg.packet.notify.image_size", \
		FT_UINT8, BASE_CUSTOM, \
		gg_format_size_kib, 0, \
		"maximum allowed received image size (in kiB)", HFILL } \
	}, \
	{ &gg_dissect_notify_hf_flags, \
		{ "connection flags", "gg.packet.notify.flags", \
		FT_UINT32, BASE_HEX, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_notify_hf_description_size, \
		{ "description length", "gg.packet.notify.description_size", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		"length of description field", HFILL } \
	}, \
	{ &gg_dissect_notify_hf_description, \
		{ "description", "gg.packet.notify.description", \
		FT_STRING, BASE_NONE, \
		NULL, 0, \
		"status description", HFILL } \
	}, \
	\
	{ &gg_dissect_notify_hf_firstlast_record, \
		{ "user", "gg.packet.notify.firstlast.user", \
		FT_BYTES, BASE_NONE, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_notify_hf_firstlast_uin, \
		{ "user identifier", "gg.packet.notify.firstlast.uin", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_notify_hf_firstlast_type, \
		{ "type", "gg.packet.notify.firstlast.type", \
		FT_UINT8, BASE_HEX, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_notify_hf_firstlast_type_buddy, \
		{ "buddy", "gg.packet.notify.firstlast.type.buddy", \
		FT_BOOLEAN, 8, \
		TFS(&tfs_set_notset), 0x01, \
		"user is on buddy list", HFILL } \
	}, \
	{ &gg_dissect_notify_hf_firstlast_type_friend, \
		{ "friend", "gg.packet.notify.firstlast.type.friend", \
		FT_BOOLEAN, 8, \
		TFS(&tfs_set_notset), 0x02, \
		"user gets our status in \"friends only\" mode", HFILL } \
	}, \
	{ &gg_dissect_notify_hf_firstlast_type_blocked, \
		{ "blocked", "gg.packet.notify.firstlast.type.blocked", \
		FT_BOOLEAN, 8, \
		TFS(&tfs_set_notset), 0x04, \
		NULL, HFILL } \
	}, \
	\
	{ &gg_dissect_notify_hf_userdata_type, \
		{ "type", "gg.packet.userdata.type", \
		FT_UINT32, BASE_HEX_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_notify_hf_userdata_usernum, \
		{ "count", "gg.packet.userdata.count", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_notify_hf_userdata_user, \
		{ "user", "gg.packet.userdata.user", \
		FT_BYTES, BASE_NONE, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_notify_hf_userdata_uin, \
		{ "user identifier", "gg.packet.userdata.user.uin", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_notify_hf_userdata_attrnum, \
		{ "count", "gg.packet.userdata.user.count", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_notify_hf_userdata_attr, \
		{ "attribute", "gg.packet.userdata.user.attr", \
		FT_BYTES, BASE_NONE, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_notify_hf_userdata_attr_name_size, \
		{ "name length", "gg.packet.userdata.user.attr.name_size", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_notify_hf_userdata_attr_name, \
		{ "name", "gg.packet.userdata.user.attr.name", \
		FT_STRING, BASE_NONE, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_notify_hf_userdata_attr_type, \
		{ "type", "gg.packet.userdata.user.attr.type", \
		FT_UINT32, BASE_HEX_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_notify_hf_userdata_attr_value_size, \
		{ "value length", "gg.packet.userdata.user.attr.value_size", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_notify_hf_userdata_attr_value, \
		{ "value", "gg.packet.userdata.user.attr.value", \
		FT_STRING, BASE_NONE, \
		NULL, 0, \
		NULL, HFILL } \
	}, \


extern void gg_dissect_notify_status80(tvbuff_t *tvb, proto_tree *tree);

extern void gg_dissect_notify_reply80(tvbuff_t *tvb, proto_tree *tree);

extern void gg_dissect_notify_firstlast(tvbuff_t *tvb, proto_tree *tree);

extern void gg_dissect_notify_new_status80(tvbuff_t *tvb, proto_tree *tree);

extern void gg_dissect_notify_user_data(tvbuff_t *tvb, proto_tree *tree);

#endif
