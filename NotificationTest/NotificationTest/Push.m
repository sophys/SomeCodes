//
//  Push.m
//  NotificationTest
//
//  Created by Ysan on 14-4-4.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import "Push.h"

@implementation Push

-(id)init
{
    if([super init])
    {
         [[NSNotificationCenter defaultCenter] postNotificationName:kChangeNotification object:@"Hello World"];
    }
    return self;
}

@end
