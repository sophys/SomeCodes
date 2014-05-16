//
//  NSArray+Block.h
//  BlockTest
//
//  Created by Ysan on 14-4-3.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSArray (Block)

+(NSArray *) arrayByFilteringArray:(NSArray*)source withCallback:(BOOL (^)(id))callBack;
@end
