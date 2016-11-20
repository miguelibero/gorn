#ifndef __gorn__AttributeTransformation__
#define __gorn__AttributeTransformation__

#include <glm/glm.hpp>
#include <functional>
#include <gorn/gl/AttributeKind.hpp>
class buffer;

namespace gorn
{
	class VertexAttributeDefinition;

	class AttributeTransformation
	{
	public:
		typedef AttributeType Type;
		typedef VertexAttributeDefinition Definition;
		typedef std::function<void(const VertexAttributeDefinition& def, buffer& elms, const glm::mat4& transform)> Function;

		AttributeTransformation() = delete;
		static void position(const Definition& def, buffer& elms, const glm::mat4& trans);
		static void normal(const Definition& def, buffer& elms, const glm::mat4& trans);
		static Function create(Type type);
	};
}

#endif

