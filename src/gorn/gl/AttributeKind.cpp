#include <gorn/gl/AttributeKind.hpp>

namespace gorn
{
	AttributeKind::AttributeKind(Type type) :
	_type(type), _index(0)
	{
	}

	AttributeKind::AttributeKind(const std::string& name):
	_name(name), _type(Type::Custom)
	{
	}

	AttributeKind::AttributeKind(const char* name) :
	_name(name), _type(Type::Custom)
	{
	}

	AttributeKind::AttributeKind(const std::string& name, Type type, int idx):
	_name(name), _type(type), _index(idx)
	{

	}

	AttributeKind::AttributeKind(Type type, int idx):
	_type(type), _index(idx)
	{

	}

	AttributeKind::Type AttributeKind::getType() const
	{
		return _type;
	}

	int AttributeKind::getIndex() const
	{
		return _index;
	}

	const std::string& AttributeKind::getName() const
	{
		return _name;
	}

	bool AttributeKind::match(const AttributeKind& other) const
	{
		if (_type != other._type)
		{
			return false;
		}
		if (_type == Type::Custom)
		{
			return _name == other._name;
		}
		return _index == other._index;
	}

	bool AttributeKind::operator==(const AttributeKind& other) const
	{
		return _name == other._name && _index == other._index && _type == other._type;
	}
}

namespace std
{
	size_t hash<gorn::AttributeKind>::operator()(const gorn::AttributeKind& x) const
	{
		return ((hash<string>()(x.getName())
			^ (hash<int>()((int)x.getType()) << 1)) >> 1)
			^ (hash<int>()(x.getIndex()) << 1);
	}
}