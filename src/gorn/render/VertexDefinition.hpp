#ifndef __gorn__VertexDefinition__
#define __gorn__VertexDefinition__

#include <gorn/render/AttributeDefinition.hpp>
#include <map>

namespace gorn
{
    class VertexArray;
    class VertexBuffer;
    class Program;

	class VertexDefinition
	{
    private:
        std::map<std::string, AttributeDefinition> _attributes;

	public:

        VertexDefinition();

        AttributeDefinition& setAttribute(const std::string& name);

        const std::map<std::string, AttributeDefinition>& getAttributes() const;
	};
}

#endif

