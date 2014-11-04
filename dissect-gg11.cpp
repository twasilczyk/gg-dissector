#include "packet-gg.hpp"

#include "dissect-gg11.hpp"
#include "dissect-protobuf.hpp"

#include <vector>
#include <iostream>

using namespace std;

gint ett_option = -1;
gint ett_mpanotify_data = -1;

class GGPDisplayOption : public PBDisplay
{
public:
	GGPDisplayOption():PBDisplay(PBTYPE_STRING) {}
	virtual void display(proto_tree *tree, tvbuff_t *tvb);
};

class GGPDisplayJson : public PBDisplay
{
public:
	GGPDisplayJson():PBDisplay(PBTYPE_STRING) {}
	virtual void display(proto_tree *tree, tvbuff_t *tvb);
};

static vector<shared_ptr<PBDisplay>> packet_login105 = {
	make_shared<PBDisplayString>(GGPFieldString("language", "gg.login105.language", NULL)),
	make_shared<PBDisplayUIN>(GGPFieldString("uin", "gg.login105.uin", NULL)),
	make_shared<PBDisplayBlob>(GGPFieldBlob("hash", "gg.login105.hash", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT64("dummy1", "gg.login105.dummy1", NULL)),
	make_shared<PBDisplayUINT32>(GGPFieldHEX32("dummy2", "gg.login105.dummy2", NULL)),
	make_shared<PBDisplayUINT32>(GGPFieldHEX32("dummy3", "gg.login105.dummy3", NULL)),
	make_shared<PBDisplayString>(GGPFieldString("client", "gg.login105.client", NULL)),
	make_shared<PBDisplayUINT32>(GGPFieldHEX32("initial_status", "gg.login105.initial_status", NULL)),
	make_shared<PBDisplayString>(GGPFieldString("initial_descr", "gg.login105.initial_descr", NULL)),
	make_shared<PBDisplayBlob>(GGPFieldBlob("dummy4", "gg.login105.dummy4", NULL)),
	make_shared<PBDisplayString>(GGPFieldString("supported_features", "gg.login105.supported_features", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT64("dummy5", "gg.login105.dummy5", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT64("dummy6", "gg.login105.dummy6", NULL)),
	make_shared<PBDisplayUINT32>(GGPFieldUINT32("dummy7", "gg.login105.dummy7", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT64("dummy8", "gg.login105.dummy8", NULL)),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayVarint>(GGPFieldUINT64("dummy10", "gg.login105.dummy10", NULL)),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayBlob>(GGPFieldBlob("dummy15", "gg.login105.dummy15", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT64("dummy16", "gg.login105.dummy16", NULL)),
	make_shared<PBDisplayBlob>(GGPFieldBlob("dummy17", "gg.login105.dummy17", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT64("dummy18", "gg.login105.dummy18", NULL)),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayBlob>(GGPFieldBlob("dummy21", "gg.login105.dummy21", NULL)),
};

static vector<shared_ptr<PBDisplay>> packet_login105_ok = {
	make_shared<PBDisplayVarint>(GGPFieldUINT64("dummy1", "gg.login105ok.dummy1", NULL)),
	make_shared<PBDisplayString>(GGPFieldString("dummyhash", "gg.login105ok.dummyhash", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT64("uin", "gg.login105ok.uin", NULL)),
	make_shared<PBDisplayTimestamp>(GGPFieldTimestamp("server_time", "gg.login105ok.server_time", NULL)),
};

static vector<shared_ptr<PBDisplay>> packet_send_msg110 = {
	make_shared<PBDisplayUIN>(GGPFieldString("recipient", "gg.sendmsg110.recipient", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT64("dummy1", "gg.sendmsg110.dummy1", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT64("seq", "gg.sendmsg110.seq", NULL)),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayString>(GGPFieldString("msg_plain", "gg.sendmsg110.msg_plain", NULL)),
	make_shared<PBDisplayString>(GGPFieldString("msg_xhtml", "gg.sendmsg110.xhtml", NULL)),
	make_shared<PBDisplayBlob>(GGPFieldBlob("dummy3", "gg.sendmsg110.dummy3", NULL)),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayUINT64>(GGPFieldHEX64("chat_id", "gg.sendmsg110.chat_id", NULL)),
};

static vector<shared_ptr<PBDisplay>> packet_recv_msg110 = {
	make_shared<PBDisplayUIN>(GGPFieldString("sender", "gg.recvmsg110.sender", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldHEX64("flags", "gg.recvmsg110.flags", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT64("seq", "gg.recvmsg110.seq", NULL)),
	make_shared<PBDisplayUINT32>(GGPFieldUINT32("time", "gg.recvmsg110.time", NULL)),
	make_shared<PBDisplayString>(GGPFieldString("msg_plain", "gg.recvmsg110.msg_plain", NULL)),
	make_shared<PBDisplayString>(GGPFieldString("msg_xhtml", "gg.recvmsg110.msg_xhtml", NULL)),
	make_shared<PBDisplayBlob>(GGPFieldBlob("data", "gg.recvmsg110.data", NULL)),
	make_shared<PBDisplayUnknown>(),
	make_shared<PBDisplayUINT64>(GGPFieldHEX64("msg_id", "gg.recvmsg110.msg_id", NULL)),
	make_shared<PBDisplayUINT64>(GGPFieldHEX64("chat_id", "gg.recvmsg110.chat_id", NULL)),
	make_shared<PBDisplayUINT64>(GGPFieldHEX64("conv_id", "gg.recvmsg110.conv_id", NULL)),
};

static vector<shared_ptr<PBDisplay>> packet_imtoken = {
	make_shared<PBDisplayString>(GGPFieldString("imtoken", "gg.imtoken.imtoken", NULL)),
};

GGPFieldBlob option_field("option", "gg.options.option", NULL);
static vector<shared_ptr<PBDisplay>> packet_options = {
	make_shared<GGPDisplayOption>(),
	make_shared<PBDisplayVarint>(GGPFieldUINT64("dummy1", "gg.options.dummy1", NULL)),
};
GGPFieldString option_key_field("key", "gg.options.option.key", NULL);
GGPFieldString option_value_field("value", "gg.options.option.value", NULL);
static vector<shared_ptr<PBDisplay>> packet_options_option = {
	make_shared<PBDisplayString>(option_key_field),
	make_shared<PBDisplayString>(option_value_field),
};

static vector<shared_ptr<PBDisplay>> packet_lastdates = {
	make_shared<PBDisplayVarint>(GGPFieldUINT64("dummy1", "gg.lastdates.dummy1", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT64("dummy2", "gg.lastdates.dummy2", NULL)),
	make_shared<PBDisplayVITimestamp>(GGPFieldTimestamp("dummydate1", "gg.lastdates.dummydate1", NULL)),
	make_shared<PBDisplayVITimestamp>(GGPFieldTimestamp("dummydate2", "gg.lastdates.dummydate2", NULL)),
	make_shared<PBDisplayVITimestamp>(GGPFieldTimestamp("dummydate3", "gg.lastdates.dummydate3", NULL)),
};

GGPFieldString packet_mpanotify_data("data", "gg.mpanotify.data", NULL);
static vector<shared_ptr<PBDisplay>> packet_mpanotify = {
	make_shared<PBDisplayVarint>(GGPFieldUINT64("dummy1", "gg.mpanotify.dummy1", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT64("dummy2", "gg.mpanotify.dummy2", NULL)),
	make_shared<GGPDisplayJson>(),
	make_shared<PBDisplayString>(GGPFieldString("content_type", "gg.mpanotify.content_type", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT64("dummyid", "gg.mpanotify.dummyid", NULL)),
};

const value_string ack110_types[] = {
	{ 1, "MSG" },
	{ 2, "CHAT" },
	{ 3, "CHAT_INFO" },
	{ 6, "MPA" },
	{ 7, "TRANSFER_INFO" },
	{ 0, NULL }
};

static vector<shared_ptr<PBDisplay>> packet_ack110 = {
	make_shared<PBDisplayEnum>(GGPFieldEnum("type", "gg.ack110.type", NULL, VALS(ack110_types))),
	make_shared<PBDisplayVarint>(GGPFieldUINT64("seq", "gg.ack110.seq", NULL)),
	make_shared<PBDisplayVarint>(GGPFieldUINT64("dummy1", "gg.ack110.dummy1", NULL)),
};

void init_gg11()
{
	static gint *ett[] = {
		&ett_option,
		&ett_mpanotify_data
	};

	proto_register_subtree_array(ett, array_length(ett));
}

void dissect_gg11_login105(tvbuff_t *tvb, proto_tree *tree)
{
	dissect_protobuf(tvb, tree, packet_login105);
}

void dissect_gg11_login105_ok(tvbuff_t *tvb, proto_tree *tree)
{
	dissect_protobuf(tvb, tree, packet_login105_ok);
}

void dissect_gg11_send_msg110(tvbuff_t *tvb, proto_tree *tree)
{
	dissect_protobuf(tvb, tree, packet_send_msg110);
}

void dissect_gg11_recv_msg110(tvbuff_t *tvb, proto_tree *tree)
{
	dissect_protobuf(tvb, tree, packet_recv_msg110);
}

void dissect_gg11_imtoken(tvbuff_t *tvb, proto_tree *tree)
{
	dissect_protobuf(tvb, tree, packet_imtoken);
}

void dissect_gg11_options(tvbuff_t *tvb, proto_tree *tree)
{
	dissect_protobuf(tvb, tree, packet_options);
}

void dissect_gg11_lastdates(tvbuff_t *tvb, proto_tree *tree)
{
	dissect_protobuf(tvb, tree, packet_lastdates);
}

void dissect_gg11_mpanotify(tvbuff_t *tvb, proto_tree *tree)
{
	dissect_protobuf(tvb, tree, packet_mpanotify);
}

void dissect_gg11_ack110(tvbuff_t *tvb, proto_tree *tree)
{
	dissect_protobuf(tvb, tree, packet_ack110);
}

void GGPDisplayOption::display(proto_tree *tree, tvbuff_t *tvb)
{
	proto_item *ti = proto_tree_add_item(tree, option_field, tvb, 0, tvb_length(tvb), 0);
	proto_tree *subtree = proto_item_add_subtree(ti, ett_option);

	dissect_protobuf(tvb, subtree, packet_options_option);

	GPtrArray *fields = proto_all_finfos(subtree);
	if (fields->len == 3) {
		field_info *key_f = (field_info*)g_ptr_array_index(fields, 1);
		field_info *value_f = (field_info*)g_ptr_array_index(fields, 2);

		char *key = NULL, *value = NULL;

		if (key_f)
			key = fvalue_to_string_repr(&key_f->value, FTREPR_DISPLAY, NULL);
		if (value_f)
			value = fvalue_to_string_repr(&value_f->value, FTREPR_DISPLAY, NULL);

		if (key && value)
			proto_item_set_text(ti, "option: %s=%s", key, value);

		free(key);
		free(value);
	}

	g_ptr_array_free(fields, TRUE);

}

void GGPDisplayJson::display(proto_tree *tree, tvbuff_t *tvb)
{
	proto_item *ti = proto_tree_add_item(tree, packet_mpanotify_data, tvb, 0, tvb_length(tvb), 0);

	if (!json_dissector)
		return;

	proto_tree *subtree = proto_item_add_subtree(ti, ett_mpanotify_data);

	packet_info *pinfo = tree->tree_data->pinfo;

	void *private_data = pinfo->private_data;
	pinfo->private_data = NULL;

	call_dissector(json_dissector, tvb, pinfo, subtree);

	pinfo->private_data = private_data;
}
