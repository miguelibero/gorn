#ifndef __gorn__VertexDefinition__
#define __gorn__VertexDefinition__

#include <gorn/render/AttributeBindingDefinition.hpp>
#include <map>

namespace gorn
{
    class VertexArray;
    class VertexBuffer;
    class Program;

	class VertexDefinition
	{
    private:
        std::map<std::string, AttributeBindingDefinition> _attributeBindings;

	public:

        VertexDefinition();

        AttributeBindingDefinition& defineAttribute(const std::string& name);

        const std::map<std::string, AttributeBindingDefinition>& getAttributeBindings() const;
	};
}

#endif

