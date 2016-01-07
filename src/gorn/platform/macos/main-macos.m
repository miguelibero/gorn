#include <AppKit/AppKit.h>
#include "GameView.h"

int main(int argc, char * argv[]) {
    @autoreleasepool {        
        [NSApplication sharedApplication];
        NSWindow* window = [[NSWindow alloc] init];
        GameView* view = [[GameView alloc] initWitWindow:window];
        [window orderFrontRegardless];
        [NSApp run];
        [view finalize];
        return 0;
    }
}
