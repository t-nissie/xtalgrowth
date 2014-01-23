#include <Foundation/Foundation.h>
#include <stdio.h>
#include <AppKit/AppKit.h>
int main (int argc, char **argv) {
    NSObject *obj = [[NSObject alloc] init];
    NSView *view = [[NSView alloc] init];
    fprintf(stderr, "Object: %s\n", [[obj description] UTF8String]);
    fprintf(stderr, "Object: %s\n", [[view description] UTF8String]);
    return 0;
}
