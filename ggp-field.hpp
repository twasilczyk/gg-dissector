extern "C" {
#include <epan/packet.h>
}

#include <vector>

class GGPField
{
private:
	const char *name;
	const char *abbrev;
	const char *blurb;
	static std::vector<GGPField*> all_fields;
	int hf_id;

protected:
	virtual void fill_header_field_info(header_field_info &info) = 0;

public:
	GGPField(const char *name, const char *abbrev, const char *blurb);
	~GGPField();

	static void register_all(int parent);

	operator int();
};

class GGPFieldUINT32 : public GGPField
{
private:
	virtual void fill_header_field_info(header_field_info &info);

public:
	GGPFieldUINT32(const char *name, const char *abbrev, const char *blurb);
};
