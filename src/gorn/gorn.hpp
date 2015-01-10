#ifndef __gorn__
#define __gorn__

#include <gorn/base/Application.hpp>
#include <gorn/render/RenderContext.hpp>
#include <gorn/render/RenderSystem2D.hpp>
#include <gorn/render/MaterialDefinition.hpp>
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/VertexDefinition.hpp>
#include <gorn/render/AttributeDefinition.hpp>
#include <gorn/render/UniformValue.hpp>
#include <gorn/render/Kinds.hpp>
#include <gorn/asset/Image.hpp>
#include <gorn/sprite/GdxSpriteAtlasLoader.hpp>
#include <gorn/sprite/CocosSpriteAtlasLoader.hpp>
#include <gorn/sprite/SpriteAtlas.hpp>
#include <gorn/sprite/Sprite.hpp>

#ifdef GORN_PLATFORM_LINUX
#include <gorn/platform/linux/LocalFileLoader.hpp>
#include <gorn/platform/linux/PngImageLoader.hpp>
#elif GORN_PLATFORM_ANDROID
#include <gorn/platform/android/BundleFileLoader.hpp>
#include <gorn/platform/android/GraphicsImageLoader.hpp>
#endif

#endif

