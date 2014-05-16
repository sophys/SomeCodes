//
//  Delegate.h
//  DelegateTest
//
//  Created by Ysan on 14-4-4.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Owner.h"
@interface Delegate : NSObject<ChangeValueDelegate>
{
    Owner *o;
}
@property NSString   *myString;
@end
