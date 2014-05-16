//
//  ModalViewController.m
//  DelegateUIKit
//
//  Created by Ysan on 14-4-4.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import "ModalViewController.h"

@interface ModalViewController ()

@end

@implementation ModalViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor grayColor];
    _textField = [[UITextField alloc] initWithFrame:CGRectMake(70, 100, 180, 30)];
    _textField.borderStyle = UITextBorderStyleRoundedRect;
    [self.view addSubview:_textField];
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    button.frame = CGRectMake(320/2-140/2, 180, 140, 40);
    [button setTitle:@"dismiss" forState:UIControlStateNormal];
    [button addTarget:self action:@selector(dismiss) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:button];
	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)dismiss{
    if ([self.delegate respondsToSelector:@selector(textChange:)]) {
        
        [self.delegate textChange:_textField.text];
    }
    
    if ([[UIDevice currentDevice].systemVersion floatValue] < 6.0) {
        
        [self dismissModalViewControllerAnimated:YES];
        
    }else {
        
        [self dismissViewControllerAnimated:YES completion:^{
            
        }];
    }
}

@end
