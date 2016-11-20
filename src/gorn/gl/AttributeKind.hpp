#ifndef __gorn__AttributeKind__
#define __gorn__AttributeKind__

#include <string>
#include <unordered_map>

namespace gorn
{
	enum class AttributeType
	{
		Custom,
		Position,
		Normal,
		Color,
		TexCoords
	};

    class AttributeKind
    {
	public:
		typedef AttributeType Type;
    private:
		std::string _name;
		Type _type;
		int _index;
    public:
		AttributeKind(Type type=Type::Custom);
		AttributeKind(const std::string& name);
		AttributeKind(const char* name);
		AttributeKind(Type type, int idx);
		AttributeKind(const std::string& name, Type type, int idx = 0);

		Type getType() const;
		int getIndex() const;
		const std::string& getName() const;

		bool match(const AttributeKind& other) const;
		bool operator==(const AttributeKind& other) const;
    };
}


namespace std
{
	template <> struct hash<gorn::AttributeKind>
	{
		size_t operator()(const gorn::AttributeKind& x) const;
	};
}

#endif

