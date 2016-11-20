#ifndef __gorn__VertexAttributeDefinition__
#define __gorn__VertexAttributeDefinition__

#include <gorn/gl/Enums.hpp>
#include <gorn/gl/AttributeTransformation.hpp>
#include <gorn/gl/AttributeKind.hpp>
#include <string>
#include <buffer.hpp>
#include <glm/glm.hpp>

class buffer;

namespace gorn
{
    class VertexArray;
    class VertexBuffer;
    class Program;

    class VertexAttributeDefinition
    {
	public:
		typedef AttributeTransformation::Function Transformation;
		typedef AttributeKind Kind;
    private:
		Kind _kind;
        bool _normalized;
        BasicType _type;
        size_t _count;
        size_t _stride;
        BasicType _strideType;
        size_t _offset;
        BasicType _offsetType;
		Transformation _transformation;
		buffer _defaultValue;
    public:

        VertexAttributeDefinition(const Kind& kind = Kind());

        VertexAttributeDefinition& withBasicType(BasicType type);
        VertexAttributeDefinition& withNormalized(bool enabled);
        VertexAttributeDefinition& withCount(size_t count);
        VertexAttributeDefinition& withStride(size_t stride);
        VertexAttributeDefinition& withOffset(size_t offset);
        VertexAttributeDefinition& withStride(size_t stride, BasicType type);
        VertexAttributeDefinition& withOffset(size_t offset, BasicType type);
        VertexAttributeDefinition& withTransformation(const Transformation& trans);
		VertexAttributeDefinition& withDefaultValue(const buffer& data);
    
        const Kind& getKind() const;
        BasicType getBasicType() const;
        bool getNormalized() const;
        size_t getCount() const;
        size_t getStride() const;
        size_t getOffset() const;
        BasicType getStrideType() const;
        BasicType getOffsetType() const;
        size_t getElementSize() const;
		size_t getTypeSize() const;
		const buffer& getDefaultValue() const;
		bool isTransformed() const;
		void transform(buffer& elms, const glm::mat4& transform) const;
    };
}

#endif

