//
//  main.m
//  BlockTest
//
//  Created by Ysan on 14-4-3.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//
// 破船blog里边关于block的示例
//http://beyondvincent.com/blog/archives/
#import <Foundation/Foundation.h>
#import "Car.h"
#import "NSArray+Block.h"

int main(int argc, const char * argv[])
{

    @autoreleasepool {
        Car *theCar = [[Car alloc]init];
        
        [theCar driveForDuration:10 withVariableSpeed:^(double time){ return time + 5.0; } steps:100];
        NSLog(@"FirstDemo %f",theCar.odometer);
        
        
        NSArray *arr1;
        NSArray *arr2;
        
        arr1 = [NSArray arrayWithObjects:@"Hello World!",[NSDate date],nil];
        arr2 = [NSArray arrayByFilteringArray:arr1 withCallback:^(id element){
            return [element isKindOfClass:[NSString class]];}];
        NSLog(@"SecondDemo %@",arr2);
    }
    return 0;
}

