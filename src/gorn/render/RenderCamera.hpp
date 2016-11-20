#ifndef __gorn__RenderCamera__
#define __gorn__RenderCamera__

#include <gorn/gl/UniformValue.hpp>
#include <gorn/gl/BlendMode.hpp>
#include <gorn/base/Frustum.hpp>
#include <glm/glm.hpp>

namespace gorn
{
	class RenderCamera
	{
	public:
		typedef std::vector<int> Layers;
	private:
		glm::mat4 _view;
		glm::mat4 _proj;
		glm::vec3 _position;
		Frustum _frustum;
		bool _dirty;
		UniformValueMap _uniformValues;
		Layers _layers;
	public:
		RenderCamera();
		RenderCamera& withView(const glm::mat4& view);
		RenderCamera& withProjection(const glm::mat4& proj);
		RenderCamera& withUniformValue(const UniformKind& kind, const UniformValue& value);
		RenderCamera& withUniformValues(const UniformValueMap& values);
		RenderCamera& withLayer(int layer);
		RenderCamera& withLayers(const Layers& layers);

		void update();
		const UniformValueMap& getUniformValues() const;
		const Frustum& getFrustum() const;
		const Layers& getLayers() const;

		bool matchesLayers(const Layers& layers) const;
		Ray getScreenPointRay(const glm::vec2& p) const;
		glm::vec2 getRayScreenPoint(const Ray& p) const;
	};

}

#endif
