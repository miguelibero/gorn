#include <gorn/gl/UniformKind.hpp>

namespace gorn
{
	UniformKind::UniformKind(Type type) :
	_type(type), _index(0)
	{
	}

	UniformKind::UniformKind(const std::string& name):
	_name(name), _type(Type::Custom)
	{
	}

	UniformKind::UniformKind(const char* name) :
	_name(name), _type(Type::Custom)
	{
	}

	UniformKind::UniformKind(const std::string& name, Type type, int idx):
	_name(name), _type(type), _index(idx)
	{

	}

	UniformKind::UniformKind(Type type, int idx):
	_type(type), _index(idx)
	{

	}

	UniformKind::Type UniformKind::getType() const
	{
		return _type;
	}

	int UniformKind::getIndex() const
	{
		return _index;
	}

	const std::string& UniformKind::getName() const
	{
		return _name;
	}

	bool UniformKind::match(const UniformKind& other) const
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

	bool UniformKind::operator==(const UniformKind& other) const
	{
		return _name == other._name && _index == other._index && _type == other._type;
	}
}

namespace std
{
	size_t hash<gorn::UniformKind>::operator()(const gorn::UniformKind& x) const
	{
		return ((hash<string>()(x.getName())
			^ (hash<int>()((int)x.getType()) << 1)) >> 1)
			^ (hash<int>()(x.getIndex()) << 1);
	}
}