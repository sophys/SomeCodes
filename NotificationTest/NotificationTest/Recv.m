//
//  Recv.m
//  NotificationTest
//
//  Created by Ysan on 14-4-4.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import "Recv.h"

@implementation Recv

-(id)init
{
    if ([super init]) {
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(changeLabelText:) name:kChangeNotification object:nil];
    }
    return self;
}

-(void)changeLabelText:(NSNotification *)notification
{
    NSLog(@"----%@-----",notification);
}
@end
