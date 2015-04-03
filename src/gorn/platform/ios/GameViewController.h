//
//  GameViewController.h
//  gorn
//
//  Created by mibero on 14/10/14.
//  Copyright (c) 2014 Miguel Ibero. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

@interface GameViewController : GLKViewController
- (void)applicationDidEnterBackground:(UIApplication *)application;
- (void)applicationWillEnterForeground:(UIApplication *)application;
@end
