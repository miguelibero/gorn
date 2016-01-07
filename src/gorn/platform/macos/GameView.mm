//
//  GameView.m
//  gorn
//
//  Created by Miguel Ibero on 4/1/16.
//  Copyright © 2016 Miguel Ibero. All rights reserved.
//

#import "GameView.h"
#include <gorn/base/Application.hpp>

@interface GameView()
{
    std::unique_ptr<gorn::Application> _app;
    CVDisplayLinkRef _displayLink;
}
@end

@implementation GameView

-(id)initWitWindow:(NSWindow *)window
{
    NSOpenGLPixelFormatAttribute pixelFormatAttributes[] =
    {
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        NSOpenGLPFAColorSize    , 24                           ,
        NSOpenGLPFAAlphaSize    , 8                            ,
        NSOpenGLPFADoubleBuffer ,
        NSOpenGLPFAAccelerated  ,
        0
    };
    NSOpenGLPixelFormat* format = [[NSOpenGLPixelFormat alloc] initWithAttributes:pixelFormatAttributes];
    if(self == [super initWithFrame:window.frame pixelFormat:format])
    {
        _app = std::move(gorn::main());
        auto size = _app->getSize();
        [window setContentSize:NSMakeSize(size.x, size.y)];
        [window setStyleMask:(NSTitledWindowMask | NSClosableWindowMask | NSResizableWindowMask)];
        [window setTitle:[NSString stringWithUTF8String:_app->getName().c_str()]];
        window.contentView = self;
        [window setDelegate:self];
    }
    return self;
}


// This is the renderer output callback function
static CVReturn DisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* ctx)
{
    @autoreleasepool {
        [(__bridge GameView*)ctx getFrameForTime:outputTime];
    }
    return kCVReturnSuccess;
}


-(void)prepareOpenGL
{
    [super prepareOpenGL];
    if(_app)
    {
        _app->realLoad();
    }
    
    // Synchronize buffer swaps with vertical refresh rate
    GLint swapInt = 1;
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
    
    // Create a display link capable of being used with all active displays
    CVDisplayLinkCreateWithActiveCGDisplays(&_displayLink);
    
    // Set the display link for the current renderer
    CGLContextObj cglContext = [[self openGLContext] CGLContextObj];
    CGLPixelFormatObj cglPixelFormat = [[self pixelFormat] CGLPixelFormatObj];
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(_displayLink, cglContext, cglPixelFormat);
    
    // Set the renderer output callback function
    CVDisplayLinkSetOutputCallback(_displayLink, &DisplayLinkCallback, (__bridge void*)self);
    
    // Activate the display link
    CVDisplayLinkStart(_displayLink);
}


- (void)getFrameForTime:(const CVTimeStamp*)outputTime
{
    NSOpenGLContext* ctx = [self openGLContext];
    [ctx makeCurrentContext];
    CGLLockContext([ctx CGLContextObj]);
    
    if(_app)
    {
        float deltaTime = 1.0f / (outputTime->rateScalar * (double)outputTime->videoTimeScale / (double)outputTime->videoRefreshPeriod);
        _app->realUpdate(deltaTime);
    }
    
    CGLFlushDrawable([ctx CGLContextObj]);
    CGLUnlockContext([ctx CGLContextObj]);
}

-(void)windowWillMiniaturize:(NSNotification *)notification
{
    if(_app)
    {
        _app->realBackground();
    }
}

-(void)windowWillClose:(NSNotification *)notification
{
    if(_app)
    {
        _app->realUnload();
    }
    [[NSApplication sharedApplication] terminate:self];
}

@end
