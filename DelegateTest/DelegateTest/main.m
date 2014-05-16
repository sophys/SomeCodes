//
//  main.m
//  DelegateTest
//
//  Created by Ysan on 14-4-4.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

#import "Owner.h"
#import "Delegate.h"
int main(int argc, const char * argv[])
{

    @autoreleasepool {
        Delegate *d = [[Delegate alloc]init];
      //   [d respondsToSelector:]
        id LenderClass = objc_getClass("UIView");
        unsigned int outCount, i;
        objc_property_t *properties = class_copyPropertyList(LenderClass, &outCount);
        for (i = 0; i < outCount; i++) {
            objc_property_t property = properties[i];
            fprintf(stdout, "%s %s\n", property_getName(property), property_getAttributes(property));
                }
    }
    return 0;
}

