
#include <gorn/platform/ios/UIImageLoader.hpp>
#include <gorn/base/Exception.hpp>
#include <gorn/asset/Image.hpp>
#include <buffer.hpp>
#import <UIKit/UIKit.h>

namespace gorn
{

    bool UIImageLoader::validate(const buffer& input) const NOEXCEPT
    {
        NSData* data = [NSData dataWithBytes:input.data() length:input.size()];
        UIImage* img = [UIImage imageWithData:data];
        return img != nil;
    }
    
    Image UIImageLoader::load(const buffer& input) const
    {
        NSData* data = [NSData dataWithBytes:input.data() length:input.size()];
        UIImage* img = [UIImage imageWithData:data];
        
        CGImageRef imageRef = [img CGImage];
        NSUInteger width = CGImageGetWidth(imageRef);
        NSUInteger height = CGImageGetHeight(imageRef);
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        
        buffer raw(height * width * 4);
        NSUInteger bytesPerPixel = 4;
        NSUInteger bytesPerRow = bytesPerPixel * width;
        NSUInteger bitsPerComponent = 8;
        CGContextRef context = CGBitmapContextCreate(raw.data(), width, height,
                                                     bitsPerComponent, bytesPerRow, colorSpace,
                                                     kCGImageAlphaPremultipliedLast);
        CGColorSpaceRelease(colorSpace);
        CGContextDrawImage(context, CGRectMake(0, 0, width, height), imageRef);
        CGContextRelease(context);
        
        return Image(std::move(raw), glm::vec2(width, height), true, BasicType::UnsignedByte);
	}

}
