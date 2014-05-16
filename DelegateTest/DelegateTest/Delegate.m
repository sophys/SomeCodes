//
//  Delegate.m
//  DelegateTest
//
//  Created by Ysan on 14-4-4.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import "Delegate.h"
#import "Owner.h"

@implementation Delegate

-(id)init
{
    if ([super init]) {
        o = [[Owner alloc]init];
        o.delegate=self;
        [o chageText];
    }
    return self;
}

-(void)changeValue:(NSString *)text
{
    NSLog(@"---------%@-----------",text);
}
@end
