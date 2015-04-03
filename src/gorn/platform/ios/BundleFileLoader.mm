

#include <gorn/platform/ios/BundleFileLoader.hpp>
#include <gorn/base/Data.hpp>
#include <gorn/base/String.hpp>
#import <Foundation/Foundation.h>

namespace gorn {
    
    const char* BundleFileLoader::kPlaceholder = "%s";

    BundleFileLoader::BundleFileLoader(const std::string& nameTemplate):
    _nameTemplate(nameTemplate)
    {
    }
    
    std::string BundleFileLoader::getName(const std::string& name) const NOEXCEPT
    {
        std::string rname(_nameTemplate);
        String::replaceAll(rname, kPlaceholder, name);
        return rname;
    }
    
    bool BundleFileLoader::validate(const std::string& name) const NOEXCEPT
    {
        NSString* nsname = [NSString stringWithUTF8String:getName(name).c_str()];
        return [[NSBundle mainBundle] pathForResource:nsname ofType:nil] != nil;
    }
    
    Data BundleFileLoader::load(const std::string& name) const
    {
        NSString* nsname = [NSString stringWithUTF8String:getName(name).c_str()];
        NSString* path = [[NSBundle mainBundle] pathForResource:nsname ofType:nil];
        NSData* data = [NSData dataWithContentsOfFile:path];
        uint8_t* ptr = (uint8_t*)data.bytes;
        return Data(ptr, data.length);
    }
}
