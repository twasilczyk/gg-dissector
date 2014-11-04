#include "gg-packet-type.h"

#define GG_PACKET_NAME(type, name) { GG_PACKET_##type##_##name, #name },

const value_string gg_packet_sent_names[] = {
	GG_PACKET_NAME(SEND, NEW_STATUS)
	GG_PACKET_NAME(SEND, PONG)
	GG_PACKET_NAME(SEND, PING)
	GG_PACKET_NAME(SEND, SEND_MSG)
	GG_PACKET_NAME(SEND, LOGIN)
	GG_PACKET_NAME(SEND, ADD_NOTIFY)
	GG_PACKET_NAME(SEND, REMOVE_NOTIFY)
	GG_PACKET_NAME(SEND, NOTIFY_FIRST)
	GG_PACKET_NAME(SEND, NOTIFY_LAST)
	GG_PACKET_NAME(SEND, LIST_EMPTY)
	GG_PACKET_NAME(SEND, LOGIN_EXT)
	GG_PACKET_NAME(SEND, PUBDIR50_REQUEST)
	GG_PACKET_NAME(SEND, LOGIN60)
	GG_PACKET_NAME(SEND, USERLIST_REQUEST)
	GG_PACKET_NAME(SEND, LOGIN70)
	GG_PACKET_NAME(SEND, DCC7_INFO)
	GG_PACKET_NAME(SEND, DCC7_NEW)
	GG_PACKET_NAME(SEND, DCC7_ACCEPT)
	GG_PACKET_NAME(SEND, DCC7_REJECT)
	GG_PACKET_NAME(SEND, DCC7_ID_REQUEST)
	GG_PACKET_NAME(SEND, DCC7_ABORT)
	GG_PACKET_NAME(SEND, NEW_STATUS80BETA)
	GG_PACKET_NAME(SEND, LOGIN80BETA)
	GG_PACKET_NAME(SEND, SEND_MSG80)
	GG_PACKET_NAME(SEND, USERLIST_REQUEST80)
	GG_PACKET_NAME(SEND, LOGIN80)
	GG_PACKET_NAME(SEND, NEW_STATUS80)
	GG_PACKET_NAME(SEND, USERLIST100_REQUEST)
	GG_PACKET_NAME(SEND, RECV_MSG_ACK)
	GG_PACKET_NAME(SEND, TYPING_NOTIFY)
	GG_PACKET_NAME(SEND, OWN_DISCONNECT)
	GG_PACKET_NAME(SEND, NEW_STATUS105)
	GG_PACKET_NAME(SEND, LOGIN105)
	GG_PACKET_NAME(SEND, ACK110)
	GG_PACKET_NAME(SEND, NOTIFY105_FIRST)
	GG_PACKET_NAME(SEND, NOTIFY105_LAST)
	GG_PACKET_NAME(SEND, CHAT_LEAVE)
	GG_PACKET_NAME(SEND, CHAT_NEW)
	GG_PACKET_NAME(SEND, CHAT_INVITE)
	GG_PACKET_NAME(SEND, CHAT_SEND_MSG)
	GG_PACKET_NAME(SEND, MSG110)
	GG_PACKET_NAME(SEND, UNKNOWN1)

	{ 0, NULL }
};

const value_string gg_packet_recv_names[] = {
	GG_PACKET_NAME(RECV, WELCOME)
	GG_PACKET_NAME(RECV, STATUS)
	GG_PACKET_NAME(RECV, LOGIN_OK)
	GG_PACKET_NAME(RECV, SEND_MSG_ACK)
	GG_PACKET_NAME(RECV, PONG)
	GG_PACKET_NAME(RECV, PING)
	GG_PACKET_NAME(RECV, LOGIN_FAILED)
	GG_PACKET_NAME(RECV, RECV_MSG)
	GG_PACKET_NAME(RECV, DISCONNECTING)
	GG_PACKET_NAME(RECV, NOTIFY_REPLY)
	GG_PACKET_NAME(RECV, DISCONNECT_ACK)
	GG_PACKET_NAME(RECV, PUBDIR50_REPLY)
	GG_PACKET_NAME(RECV, STATUS60)
	GG_PACKET_NAME(RECV, USERLIST_REPLY)
	GG_PACKET_NAME(RECV, NOTIFY_REPLY60)
	GG_PACKET_NAME(RECV, NEED_EMAIL)
	GG_PACKET_NAME(RECV, LOGIN_HASH_TYPE_INVALID)
	GG_PACKET_NAME(RECV, STATUS77)
	GG_PACKET_NAME(RECV, NOTIFY_REPLY77)
	GG_PACKET_NAME(RECV, DCC7_INFO)
	GG_PACKET_NAME(RECV, DCC7_NEW)
	GG_PACKET_NAME(RECV, DCC7_ACCEPT)
	GG_PACKET_NAME(RECV, DCC7_REJECT)
	GG_PACKET_NAME(RECV, DCC7_ID_REPLY)
	GG_PACKET_NAME(RECV, DCC7_ABORTED)
	GG_PACKET_NAME(RECV, XML_EVENT)
	GG_PACKET_NAME(RECV, STATUS80BETA)
	GG_PACKET_NAME(RECV, NOTIFY_REPLY80BETA)
	GG_PACKET_NAME(RECV, XML_ACTION)
	GG_PACKET_NAME(RECV, RECV_MSG80)
	GG_PACKET_NAME(RECV, USERLIST_REPLY80)
	GG_PACKET_NAME(RECV, LOGIN_OK80)
	GG_PACKET_NAME(RECV, STATUS80)
	GG_PACKET_NAME(RECV, NOTIFY_REPLY80)
	GG_PACKET_NAME(RECV, USERLIST100_REPLY)
	GG_PACKET_NAME(RECV, USER_DATA)
	GG_PACKET_NAME(RECV, TYPING_NOTIFY)
	GG_PACKET_NAME(RECV, OWN_MESSAGE)
	GG_PACKET_NAME(RECV, OWN_RESOURCE_INFO)
	GG_PACKET_NAME(RECV, USERLIST100_VERSION)
	GG_PACKET_NAME(RECV, MSG110)
	GG_PACKET_NAME(RECV, OWN_MSG110)
	GG_PACKET_NAME(RECV, IMTOKEN)
	GG_PACKET_NAME(RECV, MPA_NOTIFY)
	GG_PACKET_NAME(RECV, LOGIN105_OK)
	GG_PACKET_NAME(RECV, PONG110)
	GG_PACKET_NAME(RECV, OPTIONS)
	GG_PACKET_NAME(RECV, CHAT_INFO)
	GG_PACKET_NAME(RECV, CHAT_INFO_UPDATE)
	GG_PACKET_NAME(RECV, CHAT_CREATED)
	GG_PACKET_NAME(RECV, CHAT_INVITE_ACK)
	GG_PACKET_NAME(RECV, SEND_MSG_ACK110)
	GG_PACKET_NAME(RECV, CHAT_RECV_MSG)
	GG_PACKET_NAME(RECV, LAST_DATES)

	{ 0, NULL }
};
