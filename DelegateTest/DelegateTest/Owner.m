//
//  Owner.m
//  DelegateTest
//
//  Created by Ysan on 14-4-4.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import "Owner.h"

@implementation Owner

-(void)chageText
{
    [self.delegate  changeValue:@"Hello World"];
}
@end
