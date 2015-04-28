#ifndef __gorn__platform__
#define __gorn__platform__

#ifdef GORN_PLATFORM_LINUX
#include <gorn/platform/LocalFileLoader.hpp>
#include <gorn/platform/linux/PngImageLoader.hpp>
#elif GORN_PLATFORM_ANDROID
#include <gorn/platform/android/AssetFileLoader.hpp>
#include <gorn/platform/android/GraphicsImageLoader.hpp>
#elif GORN_PLATFORM_IOS
#include <gorn/platform/ios/BundleFileLoader.hpp>
#include <gorn/platform/ios/UIImageLoader.hpp>
#endif

#include <gorn/platform/LocalFileLoader.hpp>
#include <gorn/platform/StbImageLoader.hpp>

#endif
