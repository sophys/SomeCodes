//
//  main.m
//  FileCopyKVO
//
//  Created by Ysan on 14-4-3.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Observer.h"

int main(int argc, const char * argv[])
{

    @autoreleasepool {
        
        // insert code here...
        NSLog(@"Hello, World!");
        Observer *ob = [[Observer alloc]init];
        [ob copy];
        
    }
    return 0;
}

