#include "gg-dissect-userlist.h"

#include <zlib.h>

int gg_dissect_userlist_hf_type = -1;
int gg_dissect_userlist_hf_version = -1;
int gg_dissect_userlist_hf_format = -1;
int gg_dissect_userlist_hf_request = -1;

void gg_dissect_userlist100_version(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, gg_dissect_userlist_hf_version, tvb, 0, 4,
		ENC_LITTLE_ENDIAN);
}

static dissector_handle_t xml_handle = NULL;

void gg_dissect_userlist100_request(tvbuff_t *tvb, proto_tree *tree, packet_info *pinfo)
{
	int offset = 0;
	tvbuff_t *xml_tvb;
	
	proto_tree_add_item(tree, gg_dissect_userlist_hf_type, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	offset += 1;

	proto_tree_add_item(tree, gg_dissect_userlist_hf_version, tvb,
		offset, 4, ENC_LITTLE_ENDIAN);
	offset += 4;

	proto_tree_add_item(tree, gg_dissect_userlist_hf_format, tvb,
		offset, 1, ENC_LITTLE_ENDIAN);
	offset += 1;
	
	// unknown1
	offset += 1;

	xml_tvb = tvb_uncompress(tvb, offset, -1);
	if (!xml_tvb)
		return;
	add_new_data_source(pinfo, xml_tvb, "Inflated request data");
	
	proto_tree_add_item(tree, gg_dissect_userlist_hf_request, xml_tvb,
		0, -1, FALSE);
	
	if (!xml_handle)
		xml_handle = find_dissector("xml");
	call_dissector(xml_handle, xml_tvb, pinfo, tree);

}
