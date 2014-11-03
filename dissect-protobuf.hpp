extern "C" {
#include <epan/packet.h>
}

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

class PBDisplayFixedint : PBDisplay
{
public:
	PBDisplayFixedint();

	virtual void display(proto_tree *tree, tvbuff_t *tvb, int id);
};

class PBDisplayVarint : PBDisplay
{
public:
	PBDisplayVarint();

	virtual void display(proto_tree *tree, tvbuff_t *tvb, int id);
};

class PBDisplayBlob : PBDisplay
{
public:
	PBDisplayBlob();

	virtual void display(proto_tree *tree, tvbuff_t *tvb, int id);
};

void dissect_protobuf(tvbuff_t *tvb, proto_tree *tree);
