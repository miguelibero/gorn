#ifndef __gorn__AttributeDefinition__
#define __gorn__AttributeDefinition__

#include <gorn/gl/Enums.hpp>
#include <gorn/gl/AttributeTransformation.hpp>
#include <string>
#include <glm/glm.hpp>

class buffer;

namespace gorn
{
    class VertexArray;
    class VertexBuffer;
    class Program;

    class AttributeDefinition
    {
	public:
		typedef AttributeTransformation::Function Transformation;
    private:
        std::string _name;
        bool _normalized;
        BasicType _type;
        size_t _count;
        size_t _stride;
        BasicType _strideType;
        size_t _offset;
        BasicType _offsetType;
		Transformation _transformation;
    public:

        AttributeDefinition(const std::string& name="");

        AttributeDefinition& withName(const std::string& name);
        AttributeDefinition& withType(BasicType type);
        AttributeDefinition& withNormalized(bool enabled);
        AttributeDefinition& withCount(size_t count);
        AttributeDefinition& withStride(size_t stride);
        AttributeDefinition& withOffset(size_t offset);
        AttributeDefinition& withStride(size_t stride, BasicType type);
        AttributeDefinition& withOffset(size_t offset, BasicType type);
        AttributeDefinition& withTransformation(const Transformation& trans);
    
        const std::string& getName() const;
        BasicType getType() const;
        bool getNormalized() const;
        size_t getCount() const;
        size_t getStride() const;
        size_t getOffset() const;
        BasicType getStrideType() const;
        BasicType getOffsetType() const;
        size_t getElementSize() const;
		bool isTransformed() const;
		void transform(buffer& elms, const glm::mat4& transform) const;
    };
}

#endif

