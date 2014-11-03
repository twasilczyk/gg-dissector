extern "C" {
#include <epan/packet.h>
}

#include <vector>

class PBDisplay
{
private:
	int expected_type;
public:
	PBDisplay(int expected_type);

	virtual void display(proto_tree *tree, tvbuff_t *tvb, int id, guint8 type);
	virtual void display(proto_tree *tree, tvbuff_t *tvb, int id);
	virtual void display(proto_tree *tree, tvbuff_t *tvb);
};

class PBDisplayFixedint : public PBDisplay
{
public:
	PBDisplayFixedint();

	virtual void display(proto_tree *tree, tvbuff_t *tvb, int id);
};

class PBDisplayVarint : public PBDisplay
{
public:
	PBDisplayVarint();

	virtual void display(proto_tree *tree, tvbuff_t *tvb, int id);
};

class PBDisplayBlob : public PBDisplay
{
public:
	PBDisplayBlob();

	virtual void display(proto_tree *tree, tvbuff_t *tvb, int id);
};

void dissect_protobuf(tvbuff_t *tvb, proto_tree *tree, std::vector<PBDisplay> &packet_desc);
