//
//  GameViewController.m
//  gorn
//
//  Created by mibero on 14/10/14.
//  Copyright (c) 2014 Miguel Ibero. All rights reserved.
//

#import "GameViewController.h"
#include <gorn/base/Application.hpp>

@interface GameViewController () {
    std::unique_ptr<gorn::Application> _app;
}
@property (strong, nonatomic) EAGLContext *context;

- (void)setupGL;
- (void)tearDownGL;

@end

@implementation GameViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context)
    {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    _app = std::move(gorn::main());
    
    self.preferredFramesPerSecond = _app->getPreferredFramesPerSecond();
    
    [self setupGL];
}

- (void)dealloc
{    
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context)
    {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    if(_app)
    {
        _app->realBackground();
    }
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    if(_app)
    {
        _app->realForeground();
    }
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    if(_app)
    {
        for(UITouch* touch in touches)
        {
            CGPoint p = [touch locationInView:self.view];
            p.x = p.x / self.view.bounds.size.width;
            p.y = p.y / self.view.bounds.size.height;
            p.x = 2*p.x-1;
            p.y = 1-2*p.y;
            _app->realTouch(glm::vec2(p.x, p.y));
        }
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil))
    {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context)
        {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    if(_app)
    {
        _app->realLoad();
    }
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
    if(_app)
    {
        _app->realUnload();
    }
}

- (void)update
{
    if(_app)
    {
        _app->realUpdate(self.timeSinceLastUpdate);
    }
}
@end
