extern "C" {
#include <epan/packet.h>
}

#include <vector>

class GGPField
{
private:
	static std::vector<GGPField*> all_fields;
	int hf_id;

protected:
	virtual header_field_info get_header_field_info();

public:
	GGPField();
	~GGPField();

	static void register_all(int parent);
};
