//
//  RootViewController.h
//  DelegateUIKit
//
//  Created by Ysan on 14-4-4.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ModalViewController.h"
@interface RootViewController : UIViewController<TextChangeDelegate>
{
    UITextField* _textField;
}

@end
