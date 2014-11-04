extern "C" {
#include <epan/packet.h>
}

#include "ggp-field.hpp"

#include <vector>
#include <memory>

typedef enum
{
	PBTYPE_VARINT = 0,
	PBTYPE_FIXED64 = 1,
	PBTYPE_STRING = 2,
	PBTYPE_FIXED32 = 5
} PBType;

class PBDisplay
{
protected:
	PBType expected_type;
public:
	PBDisplay(PBType expected_type);

	virtual void display(proto_tree *tree, tvbuff_t *tvb, int id, PBType type);
	virtual void display(proto_tree *tree, tvbuff_t *tvb, int id);
	virtual void display(proto_tree *tree, tvbuff_t *tvb);
};

class PBDisplayUnknown : public PBDisplay
{
public:
	PBDisplayUnknown();

	virtual void display(proto_tree *tree, tvbuff_t *tvb, int id, PBType type);
};

class PBDisplayUINT32 : public PBDisplay
{
private:
	GGPFieldUINT32 field;
public:
	PBDisplayUINT32(GGPFieldUINT32 field);

	virtual void display(proto_tree *tree, tvbuff_t *tvb);
};

class PBDisplayTimestamp : public PBDisplay
{
protected:
	GGPFieldTimestamp field;
public:
	PBDisplayTimestamp(GGPFieldTimestamp field);

	virtual void display(proto_tree *tree, tvbuff_t *tvb);
};

class PBDisplayVITimestamp : public PBDisplayTimestamp
{
public:
	PBDisplayVITimestamp(GGPFieldTimestamp field);

	virtual void display(proto_tree *tree, tvbuff_t *tvb);
};

class PBDisplayUINT64 : public PBDisplay
{
private:
	GGPFieldHEX64 field;
public:
	PBDisplayUINT64(GGPFieldHEX64 field);

	virtual void display(proto_tree *tree, tvbuff_t *tvb);
};

class PBDisplayVarint : public PBDisplay
{
private:
	GGPFieldUINT32 field;
public:
	PBDisplayVarint(GGPFieldUINT32 field);

	virtual void display(proto_tree *tree, tvbuff_t *tvb);
};

class PBDisplayUIN : public PBDisplay
{
private:
	GGPFieldString field;
public:
	PBDisplayUIN(GGPFieldString field);

	virtual void display(proto_tree *tree, tvbuff_t *tvb);
};

class PBDisplayString : public PBDisplay
{
private:
	GGPFieldString field;
public:
	PBDisplayString(GGPFieldString field);

	virtual void display(proto_tree *tree, tvbuff_t *tvb);
};

class PBDisplayBlob : public PBDisplay
{
private:
	GGPFieldBlob field;
public:
	PBDisplayBlob(GGPFieldBlob field);

	virtual void display(proto_tree *tree, tvbuff_t *tvb);
};

void dissect_protobuf(tvbuff_t *tvb, proto_tree *tree, std::vector<std::shared_ptr<PBDisplay>> &packet_desc);
void dissect_protobuf(tvbuff_t *tvb, proto_tree *tree);
