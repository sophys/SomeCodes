//
//  ModalViewController.h
//  DelegateUIKit
//
//  Created by Ysan on 14-4-4.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol TextChangeDelegate <NSObject>

-(void)textChange:(NSString*)text;

@end

@interface ModalViewController : UIViewController
{
    UITextField* _textField;
}

@property(nonatomic,retain) id<TextChangeDelegate> delegate;

@end
