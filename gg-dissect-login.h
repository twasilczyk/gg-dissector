#ifndef _GG_DISSECT_LOGIN_H
#define _GG_DISSECT_LOGIN_H

#include "packet-gg.h"

#include "gg-dissect-notify.h"

extern int gg_dissect_login_hf_welcome_seed;

extern int gg_dissect_login_hf_login80_uin;
extern int gg_dissect_login_hf_login80_language;
extern int gg_dissect_login_hf_login80_hash_type;
extern int gg_dissect_login_hf_login80_hash;
extern int gg_dissect_login_hf_login80_status;
extern int gg_dissect_login_hf_login80_statusflags;
extern int gg_dissect_login_hf_login80_flags;
extern int gg_dissect_login_hf_login80_features;
extern int gg_dissect_login_hf_login80_local_ip;
extern int gg_dissect_login_hf_login80_local_port;
extern int gg_dissect_login_hf_login80_external_ip;
extern int gg_dissect_login_hf_login80_external_port;
extern int gg_dissect_login_hf_login80_image_size;
extern int gg_dissect_login_hf_login80_version_len;
extern int gg_dissect_login_hf_login80_version;
extern int gg_dissect_login_hf_login80_description_size;
extern int gg_dissect_login_hf_login80_description;

extern int gg_dissect_login_hf_login105_unknown;
extern int gg_dissect_login_hf_login105_fragment;
extern int gg_dissect_login_hf_login105_fragment_type;
extern int gg_dissect_login_hf_login105_language_len;
extern int gg_dissect_login_hf_login105_tuin_len;
extern int gg_dissect_login_hf_login105_tuin;
extern int gg_dissect_login_hf_login105_version_len;
extern int gg_dissect_login_hf_login105_description_size;
extern int gg_dissect_login_hf_login105_userdata;
extern int gg_dissect_login_hf_login105_userdata_len;
extern int gg_dissect_login_hf_login105_hash_len;

extern const value_string gg_dissect_login_hf_login80_hash_type_names[];

#define GG_DISSECT_LOGIN_HF \
	{ &gg_dissect_login_hf_welcome_seed, \
		{ "seed", "gg.packet.welcome.seed", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		"seed for hashing password", HFILL } \
	}, \
	\
	{ &gg_dissect_login_hf_login80_uin, \
		{ "user identifier", "gg.packet.login80.uin", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		"user identifier", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login80_language, \
		{ "language", "gg.packet.login80.language", \
		FT_STRING, BASE_NONE, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_login_hf_login80_hash_type, \
		{ "hash type", "gg.packet.login80.hash_type", \
		FT_UINT8, BASE_HEX, \
		VALS(gg_dissect_login_hf_login80_hash_type_names), 0, \
		"hash type used for password", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login80_hash, \
		{ "hash", "gg.packet.login80.hash", \
		FT_BYTES, BASE_NONE, \
		NULL, 0, \
		"hashed password", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login80_status, \
		{ "status", "gg.packet.login80.status", \
		FT_UINT8, BASE_HEX, \
		VALS(gg_dissect_notify_status_names), 0, \
		"initial status", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login80_statusflags, \
		{ "status flags", "gg.packet.login80.statusflags", \
		FT_UINT24, BASE_HEX, \
		NULL, 0, \
		"initial status flags", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login80_flags, \
		{ "connection flags", "gg.packet.login80.flags", \
		FT_UINT32, BASE_HEX, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_login_hf_login80_features, \
		{ "features", "gg.packet.login80.features", \
		FT_UINT32, BASE_HEX, \
		NULL, 0, \
		"supported features", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login80_local_ip, \
		{ "local ip", "gg.packet.login80.local_ip", \
		FT_IPv4, BASE_NONE, \
		NULL, 0, \
		"local address for direct connections - unused", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login80_local_port, \
		{ "local port", "gg.packet.login80.local_port", \
		FT_UINT16, BASE_DEC, \
		NULL, 0, \
		"local port for direct connections - unused", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login80_external_ip, \
		{ "external ip", "gg.packet.login80.external_ip", \
		FT_IPv4, BASE_NONE, \
		NULL, 0, \
		"external address - unused", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login80_external_port, \
		{ "external port", "gg.packet.login80.external_port", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		"external port - unused", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login80_image_size, \
		{ "maximum image size", "gg.packet.login80.image_size", \
		FT_UINT8, BASE_CUSTOM, \
		gg_format_size_kib, 0, \
		"maximum allowed received image size (in kiB)", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login80_version_len, \
		{ "version length", "gg.packet.login80.version_len", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		"length of version field", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login80_version, \
		{ "version", "gg.packet.login80.version", \
		FT_STRING, BASE_NONE, \
		NULL, 0, \
		"client version", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login80_description_size, \
		{ "description length", "gg.packet.login80.description_size", \
		FT_UINT32, BASE_DEC, \
		NULL, 0, \
		"length of description field", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login80_description, \
		{ "description", "gg.packet.login80.description", \
		FT_STRING, BASE_NONE, \
		NULL, 0, \
		"status description", HFILL } \
	}, \
	\
	{ &gg_dissect_login_hf_login105_unknown, \
		{ "_ unknown", "gg.packet.login105.unknown", \
		FT_BYTES, BASE_NONE, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_login_hf_login105_fragment, \
		{ "fragment", "gg.packet.login105.fragment", \
		FT_BYTES, BASE_NONE, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_login_hf_login105_fragment_type, \
		{ "fragment type", "gg.packet.login105.fragment.type", \
		FT_UINT8, BASE_HEX, \
		NULL, 0, \
		"type of next fragment of login packet", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login105_language_len, \
		{ "language length", "gg.packet.login105.language_len", \
		FT_UINT8, BASE_DEC, \
		NULL, 0, \
		"language field length (most probably)", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login105_tuin_len, \
		{ "user identifier length", "gg.packet.login105.tuin_len", \
		FT_UINT8, BASE_DEC, \
		NULL, 0, \
		"text based user identifier length", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login105_tuin, \
		{ "user identifier", "gg.packet.login105.tuin", \
		FT_STRING, BASE_NONE, \
		NULL, 0, \
		"text based user identifier", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login105_version_len, \
		{ "version length", "gg.packet.login105.version_len", \
		FT_UINT8, BASE_DEC, \
		NULL, 0, \
		"length of version field", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login105_description_size, \
		{ "description length", "gg.packet.login105.description_size", \
		FT_UINT8, BASE_DEC, \
		NULL, 0, \
		"length of description field", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login105_userdata_len, \
		{ "user data length", "gg.packet.login105.userdata_len", \
		FT_UINT8, BASE_DEC, \
		NULL, 0, \
		"length of userdata field", HFILL } \
	}, \
	{ &gg_dissect_login_hf_login105_userdata, \
		{ "user data", "gg.packet.login105.userdata", \
		FT_STRING, BASE_NONE, \
		NULL, 0, \
		NULL, HFILL } \
	}, \
	{ &gg_dissect_login_hf_login105_hash_len, \
		{ "hash length", "gg.packet.login105.hash_len", \
		FT_UINT8, BASE_DEC, \
		NULL, 0, \
		"length of hash field", HFILL } \
	}, \

extern void gg_dissect_login_welcome(tvbuff_t *tvb, proto_tree *tree);

extern void gg_dissect_login_login80(tvbuff_t *tvb, proto_tree *tree);

extern void gg_dissect_login_login105(tvbuff_t *tvb, proto_tree *tree);

#endif
