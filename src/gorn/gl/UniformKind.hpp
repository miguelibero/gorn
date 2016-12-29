#ifndef __gorn__UniformKind__
#define __gorn__UniformKind__

#include <string>
#include <unordered_map>

namespace gorn
{
	enum class UniformType
	{
		Custom,
		DiffuseTexture,
		SpecularTexture,
		AmbientTexture,
		EmissiveTexture,
		HeightTexture,
		NormalTexture,
		ShininessTexture,
		OpacityTexture,
		DisplacementTexture,
		LightmapTexture,
		ReflectionTexture,
		Color,
		ModelTransform,
		NormalTransform,
		ViewTransform,
		ProjectionTransform,
		CameraTransform,
		CameraPosition
	};

    class UniformKind
    {
	public:
		typedef UniformType Type;
    private:
		std::string _name;
		Type _type;
		int _index;
    public:
		UniformKind(Type type=Type::Custom);
		UniformKind(const std::string& name);
		UniformKind(const char* name);
		UniformKind(Type type, int idx);
		UniformKind(const std::string& name, Type type, int idx = 0);

		Type getType() const;
		int getIndex() const;
		const std::string& getName() const;

		bool match(const UniformKind& other) const;
		bool operator==(const UniformKind& other) const;
    };
}


namespace std
{
	template <> struct hash<gorn::UniformKind>
	{
		size_t operator()(const gorn::UniformKind& x) const;
	};
}

#endif

