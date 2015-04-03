
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
    
    void invertImageArrayHeight(buffer& data, size_t h)
    {
        size_t c = data.size()/h;
        for(size_t y=0; y<h/2; y++)
        {
            for(size_t x=0; x<c; x++)
            {
                size_t a = y*c+x;
                size_t b = (h-y-1)*c+x;
                uint8_t t = data[a];
                data[a] = data[b];
                data[b] = t;
            }
        }
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
        
        invertImageArrayHeight(raw, height);
        
        return Image(std::move(raw), glm::vec2(width, height), true, BasicType::UnsignedByte);
	}

}
