//
//  Owner.h
//  DelegateTest
//
//  Created by Ysan on 14-4-4.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol ChangeValueDelegate <NSObject>

-(void) changeValue:(NSString*)text;

@end

@interface Owner : NSObject

@property(nonatomic,assign) id<ChangeValueDelegate>delegate;
-(void)chageText;

@end
