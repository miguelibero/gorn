//
//  PlatformBridge.mm
//  gorn
//
//  Created by mibero on 14/10/14.
//  Copyright (c) 2014 Miguel Ibero. All rights reserved.
//

#include <gorn/platform/PlatformBridge.hpp>
#import <Foundation/Foundation.h>

PlatformBridge::DataPtr PlatformBridge::readFile(const std::string& name)
{
    NSString* nsname = [NSString stringWithUTF8String:name.c_str()];
    NSString* nstype = @"";
    NSString* path = [[NSBundle mainBundle] pathForResource:nsname ofType:nstype];
    NSData* data = [NSData dataWithContentsOfFile:path];
    uint8_t* ptr = (uint8_t*)data.bytes;
    return DataPtr(new Data(ptr, ptr+data.length));
}

PlatformBridge::ImagePtr PlatformBridge::readImage(const std::string& name)
{
    return nullptr;
}
