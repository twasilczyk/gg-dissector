#include "packet-gg.h"

extern "C" {

#include <epan/packet.h>
#include <epan/prefs.h>
#include <epan/dissectors/packet-tcp.h>

}

#include <cstdio>

#include "gg-packet-type.h"
#include "gg-bitfield.h"

#include "ggp-field.hpp"

#include "dissect-gg11.hpp"

/**/

static void proto_reg_handoff_gg(void);
static void proto_register_gg(void);

/**/

extern "C" {
extern const char version[30] = VERSION;
}

static int proto_gg = -1;
static dissector_handle_t gg_handle;

/* preferences */
static guint pref_gg_port = DEFAULT_GG_PORT;
static gboolean pref_gg_reassemble_packets = TRUE;

/* gg packet header */
static GGPFieldUINT32 ggfield_packet_length
	("length", "gg.packet_length", "length of packet contents");
static GGPFieldEnum32 ggfield_sent_packet_type
	("type (sent)", "gg.sent_packet_type", "type of the sent packet", VALS(gg_packet_sent_names));
static GGPFieldEnum32 ggfield_recv_packet_type
	("type (received)", "gg.recv_packet_type", "type of the received packet", VALS(gg_packet_recv_names));
static GGPFieldBlob ggfield_blob
	("data", "gg.packet", "packet contents (unknown structure)");

/* packet detail tree */
gint ett_gg = -1;
static gint ett_gg_options = -1;

typedef enum
{
	GG_PACKET_DIRECTION_SENT,
	GG_PACKET_DIRECTION_RECV,
} gg_packet_direction;

static void dissect_gg_packet(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
	proto_item *ti;
	proto_tree *gg_tree;
	tvbuff_t *data_tvb;
	
	gg_packet_direction packet_direction;
	
	int packet_type = tvb_get_letohl(tvb, 0);
	const char *packet_type_name;
	int packet_length = tvb_get_letohl(tvb, 4);
	
	col_clear(pinfo->cinfo, COL_INFO);
	if (pinfo->destport == pref_gg_port)
	{
		packet_direction = GG_PACKET_DIRECTION_SENT;
		col_append_str(pinfo->cinfo, COL_INFO, "sent: ");
		packet_type_name = try_val_to_str(packet_type,
			gg_packet_sent_names);
	}
	else
	{
		packet_direction = GG_PACKET_DIRECTION_RECV;
		col_append_str(pinfo->cinfo, COL_INFO, "received: ");
		packet_type_name = try_val_to_str(packet_type,
			gg_packet_recv_names);
	}
	
	if (packet_type_name == NULL)
		packet_type_name = "UNKNOWN";
	col_append_str(pinfo->cinfo, COL_INFO, packet_type_name);

	if (!tree)
		return;
	
	ti = proto_tree_add_item(tree, proto_gg, tvb, 0, packet_length + 8, FALSE);
	gg_tree = proto_item_add_subtree(ti, ett_gg);
	if (packet_direction == GG_PACKET_DIRECTION_SENT)
		proto_tree_add_item(gg_tree, ggfield_sent_packet_type, tvb,
			0, 4, ENC_LITTLE_ENDIAN);
	else
		proto_tree_add_item(gg_tree, ggfield_recv_packet_type, tvb,
			0, 4, ENC_LITTLE_ENDIAN);

	proto_tree_add_item(gg_tree, ggfield_packet_length, tvb,
		4, 4, ENC_LITTLE_ENDIAN);

	if (packet_length == 0)
		return;
	
	data_tvb = tvb_new_subset_remaining(tvb, 8);
	(void)data_tvb;

	if (pinfo->destport == pref_gg_port) // sent
	{
		if (packet_type == GG_PACKET_SEND_LOGIN105)
			dissect_gg11_login105(data_tvb, gg_tree);
#if 0
		if (packet_type == GG_PACKET_SEND_LOGIN80)
			gg_dissect_login_login80(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_SEND_NOTIFY_FIRST ||
			packet_type == GG_PACKET_SEND_NOTIFY_LAST)
			gg_dissect_notify_firstlast(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_SEND_NEW_STATUS80)
			gg_dissect_notify_new_status80(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_SEND_USERLIST100_REQUEST)
			gg_dissect_userlist100_request(data_tvb, gg_tree, pinfo);
		else if (packet_type == GG_PACKET_SEND_MPA_ACK)
			gg_dissect_mpa_ack(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_SEND_CHAT_LEAVE)
			gg_dissect_chat_leave(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_SEND_CHAT_NEW)
			gg_dissect_chat_new(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_SEND_CHAT_INVITE)
			gg_dissect_chat_invite(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_SEND_MSG110)
			gg_tvb_dissect(data_tvb, gg_tree);
#endif
		else
			proto_tree_add_item(gg_tree, ggfield_blob, data_tvb, 0, packet_length, FALSE);
	}
	else // recv
	{
#if 0
		if (packet_type == GG_PACKET_RECV_WELCOME)
			gg_dissect_login_welcome(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_RECV_STATUS80)
			gg_dissect_notify_status80(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_RECV_NOTIFY_REPLY80)
			gg_dissect_notify_reply80(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_RECV_USER_DATA)
			gg_dissect_notify_user_data(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_RECV_USERLIST100_VERSION)
			gg_dissect_userlist100_version(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_RECV_IMTOKEN)
			gg_dissect_imtoken(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_RECV_MPA_NOTIFY)
			gg_dissect_mpa_notify(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_RECV_CHAT_INFO)
			gg_dissect_chat_info(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_RECV_CHAT_INFO_UPDATE)
			gg_dissect_chat_info_update(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_RECV_CHAT_CREATED)
			gg_dissect_chat_created(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_RECV_CHAT_INVITE_ACK)
			gg_dissect_chat_invite_ack(data_tvb, gg_tree);
		else if (packet_type == GG_PACKET_RECV_LAST_DATES)
			gg_tvb_dissect(data_tvb, gg_tree);
		else
#endif
			proto_tree_add_item(gg_tree, ggfield_blob, data_tvb, 0, packet_length, FALSE);
	}
}

static guint get_gg_packet_len(packet_info *pinfo, tvbuff_t *tvb, int offset)
{
	(void)pinfo;
	
	return tvb_get_letohl(tvb, offset + 4) + 8;
}

static void dissect_gg(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
	col_set_str(pinfo->cinfo, COL_PROTOCOL, "GG");
	col_clear(pinfo->cinfo,COL_INFO);
	
	tcp_dissect_pdus(tvb, pinfo, tree, pref_gg_reassemble_packets, 8,
		get_gg_packet_len, dissect_gg_packet);
}

#if 0
static void gg_format_size_kib(gchar *result, guint32 size)
{
	g_snprintf(result, ITEM_LABEL_LENGTH, "%d kiB", size);
}
#endif

extern "C" {

void plugin_register(void)
{
	proto_register_gg();
}

}

static void proto_register_gg(void)
{
	static gint *ett[] = {
		&ett_gg,
		&ett_gg_options
	};

	module_t *gg_module;

	proto_gg = proto_register_protocol (
		"Gadu-Gadu messenger Protocol", /* name */
		"GG", /* short name */
		"gg" /* abbrev */
		);
	GGPField::register_all(proto_gg);
	proto_register_subtree_array(ett, array_length(ett));

	/* Preference setting */
	gg_module = prefs_register_protocol(proto_gg, NULL);
	prefs_register_uint_preference(gg_module, "tcp_port",
		"GG port number",
		"port number for gg traffic",
		10, &pref_gg_port);
	prefs_register_bool_preference(gg_module, "reassemble",
		"Reassemble packets", NULL,
		&pref_gg_reassemble_packets);
}

extern "C" {

void plugin_reg_handoff(void)
{
	proto_reg_handoff_gg();
}

}

static void proto_reg_handoff_gg(void)
{
	static gboolean initialized = FALSE;
	static guint pref_gg_port_old;

	if (!initialized)
	{
		gg_handle = create_dissector_handle(dissect_gg, proto_gg);
		initialized = TRUE;
	}
	else
		dissector_delete_uint("tcp.port", pref_gg_port_old, gg_handle);

	dissector_add_uint("tcp.port", pref_gg_port, gg_handle);
	pref_gg_port_old = pref_gg_port;
}

