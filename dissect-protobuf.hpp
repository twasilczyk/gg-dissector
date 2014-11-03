extern "C" {
#include <epan/packet.h>
}

#include "ggp-field.hpp"

#include <vector>

typedef enum
{
	PBTYPE_VARINT = 0,
	PBTYPE_FIXED64 = 1,
	PBTYPE_STRING = 2,
	PBTYPE_FIXED32 = 5
} PBType;

class PBDisplay
{
private:
	PBType expected_type;
public:
	PBDisplay(PBType expected_type);

	virtual void display(proto_tree *tree, tvbuff_t *tvb, int id, PBType type);
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

class PBDisplayString : public PBDisplay
{
private:
	GGPFieldBlob *field;
public:
	PBDisplayString(GGPFieldBlob *field);

	virtual void display(proto_tree *tree, tvbuff_t *tvb);
};

void dissect_protobuf(tvbuff_t *tvb, proto_tree *tree, std::vector<PBDisplay*> &packet_desc);
