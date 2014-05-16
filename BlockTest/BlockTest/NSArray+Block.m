//
//  NSArray+Block.m
//  BlockTest
//
//  Created by Ysan on 14-4-3.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import "NSArray+Block.h"

@implementation NSArray (Block)
+(NSArray*) arrayByFilteringArray:(NSArray *)source withCallback:(BOOL (^)(id))callBack
{
    NSMutableArray *result = [[NSMutableArray alloc]initWithCapacity:[source count]];
    for (id element in source) {
        if (callBack(element) == YES) {
            [result addObject:element];
        }
    }
    
    return result;
}
@end
