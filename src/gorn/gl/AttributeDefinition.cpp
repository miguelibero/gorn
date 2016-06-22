#include <gorn/gl/AttributeDefinition.hpp>
#include <buffer.hpp>

namespace gorn
{
    AttributeDefinition::AttributeDefinition(const std::string& name):
    _name(name),
    _normalized(false),
    _type(BasicType::None),
    _count(1),
    _stride(0),
    _strideType(BasicType::None),
    _offset(0),
    _offsetType(BasicType::None)
    {
    }

    AttributeDefinition& AttributeDefinition::withName(const std::string& name)
    {
        _name = name;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withType(BasicType type)
    {
        _type = type;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withNormalized(bool enabled)
    {
        _normalized = enabled;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withCount(size_t count)
    {
        _count = count;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withStride(size_t stride)
    {
        _stride = stride;
        _strideType = BasicType::None;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withOffset(size_t offset)
    {
        _offset = offset;
        _offsetType = BasicType::None;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withStride(
        size_t stride, BasicType type)
    {
        _stride = stride;
        _strideType = type;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withOffset(
        size_t offset, BasicType type)
    {
        _offset = offset;
        _offsetType = type;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withTransformation(const Transformation& trans)
    {
        _transformation = trans;
        return *this;
    }

	AttributeDefinition& AttributeDefinition::withDefaultValue(const buffer& data)
	{
		_defaultValue = data;
		return *this;
	}

    const std::string& AttributeDefinition::getName() const
    {
        return _name;
    }

    BasicType AttributeDefinition::getType() const
    {
        return _type;
    }

    bool AttributeDefinition::getNormalized() const
    {
        return _normalized;
    }

    size_t AttributeDefinition::getCount() const
    {
        return _count;
    }

    size_t AttributeDefinition::getStride() const
    {
        return _stride;
    }

    size_t AttributeDefinition::getOffset() const
    {
        return _offset;
    }

    BasicType AttributeDefinition::getStrideType() const
    {
        return _strideType;
    }

    BasicType AttributeDefinition::getOffsetType() const
    {
        return _offsetType;
    }

    size_t AttributeDefinition::getElementSize() const
    {
        return getCount() * getTypeSize();
    }

	size_t AttributeDefinition::getTypeSize() const
	{
		return getBasicTypeSize(getType());
	}

	const buffer& AttributeDefinition::getDefaultValue() const
	{
		return _defaultValue;
	}

	bool AttributeDefinition::isTransformed() const
	{
		return _transformation != nullptr;
	}

	void AttributeDefinition::transform(buffer& elms, const glm::mat4& trans) const
	{
		if(_transformation != nullptr)
		{
			_transformation(*this, elms, trans);
		}
	}
}
