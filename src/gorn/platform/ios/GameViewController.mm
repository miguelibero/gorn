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
    [self touches:touches withEnded:NO];
}

-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self touches:touches withEnded:NO];
}

-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self touches:touches withEnded:YES];
}

-(void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self touches:touches withEnded:YES];
}

-(void)touches:(NSSet *)touches withEnded:(BOOL)ended
{
    if(_app == nullptr)
    {
        return;
    }
    for(UITouch* touch in touches)
    {
        CGPoint p = [touch locationInView:self.view];
        p.x = p.x / self.view.bounds.size.width;
        p.y = p.y / self.view.bounds.size.height;
        p.x = 2*p.x-1;
        p.y = 1-2*p.y;
        glm::vec2 gp(p.x, p.y);
        if(ended)
        {
            _app->realTouchEnd(gp);
        }
        else
        {
            _app->realTouch(gp);
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
