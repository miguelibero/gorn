#include <gorn/gl/VertexAttributeDefinition.hpp>
#include <buffer.hpp>

namespace gorn
{
    VertexAttributeDefinition::VertexAttributeDefinition(const Kind& kind):
    _kind(kind),
	_normalized(false),
	_type(BasicType::None),
	_count(1),
	_stride(0),
	_strideType(BasicType::None),
	_offset(0),
	_offsetType(BasicType::None)
    {
    }

    VertexAttributeDefinition& VertexAttributeDefinition::withBasicType(BasicType type)
    {
        _type = type;
        return *this;
    }

    VertexAttributeDefinition& VertexAttributeDefinition::withNormalized(bool enabled)
    {
        _normalized = enabled;
        return *this;
    }

    VertexAttributeDefinition& VertexAttributeDefinition::withCount(size_t count)
    {
        _count = count;
        return *this;
    }

    VertexAttributeDefinition& VertexAttributeDefinition::withStride(size_t stride)
    {
        _stride = stride;
        _strideType = BasicType::None;
        return *this;
    }

    VertexAttributeDefinition& VertexAttributeDefinition::withOffset(size_t offset)
    {
        _offset = offset;
        _offsetType = BasicType::None;
        return *this;
    }

    VertexAttributeDefinition& VertexAttributeDefinition::withStride(
        size_t stride, BasicType type)
    {
        _stride = stride;
        _strideType = type;
        return *this;
    }

    VertexAttributeDefinition& VertexAttributeDefinition::withOffset(
        size_t offset, BasicType type)
    {
        _offset = offset;
        _offsetType = type;
        return *this;
    }

    VertexAttributeDefinition& VertexAttributeDefinition::withTransformation(const Transformation& trans)
    {
        _transformation = trans;
        return *this;
    }

	VertexAttributeDefinition& VertexAttributeDefinition::withDefaultValue(const buffer& data)
	{
		_defaultValue = data;
		return *this;
	}

    const VertexAttributeDefinition::Kind& VertexAttributeDefinition::getKind() const
    {
        return _kind;
    }

    BasicType VertexAttributeDefinition::getBasicType() const
    {
        return _type;
    }

    bool VertexAttributeDefinition::getNormalized() const
    {
        return _normalized;
    }

    size_t VertexAttributeDefinition::getCount() const
    {
        return _count;
    }

    size_t VertexAttributeDefinition::getStride() const
    {
        return _stride;
    }

    size_t VertexAttributeDefinition::getOffset() const
    {
        return _offset;
    }

    BasicType VertexAttributeDefinition::getStrideType() const
    {
        return _strideType;
    }

    BasicType VertexAttributeDefinition::getOffsetType() const
    {
        return _offsetType;
    }

    size_t VertexAttributeDefinition::getElementSize() const
    {
        return getCount() * getTypeSize();
    }

	size_t VertexAttributeDefinition::getTypeSize() const
	{
		return getBasicTypeSize(getBasicType());
	}

	const buffer& VertexAttributeDefinition::getDefaultValue() const
	{
		return _defaultValue;
	}

	bool VertexAttributeDefinition::isTransformed() const
	{
		return _transformation != nullptr;
	}

	void VertexAttributeDefinition::transform(buffer& elms, const glm::mat4& trans) const
	{
		if(_transformation != nullptr)
		{
			_transformation(*this, elms, trans);
		}
	}
}
