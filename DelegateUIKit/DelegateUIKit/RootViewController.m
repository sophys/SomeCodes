//
//  RootViewController.m
//  DelegateUIKit
//
//  Created by Ysan on 14-4-4.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import "RootViewController.h"

@interface RootViewController ()

@end

@implementation RootViewController

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
    self.view.backgroundColor = [UIColor brownColor];
	// Do any additional setup after loading the view.
    _textField = [[UITextField alloc] initWithFrame:CGRectMake(70, 100, 180, 30)];
    _textField.borderStyle = UITextBorderStyleRoundedRect;
    [self.view addSubview:_textField];
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    button.frame = CGRectMake(320/2-140/2, 180, 140, 40);
    [button setTitle:@"presentView" forState:UIControlStateNormal];
    [button addTarget:self action:@selector(presentView) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:button];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)presentView
{
    ModalViewController *mv = [[ModalViewController alloc]init];
    mv.delegate=self;
    
    if ([[UIDevice currentDevice].systemVersion floatValue] < 6.0) {
        
        [self presentModalViewController:mv animated:YES];
        
    }else {
        
        [self presentViewController:mv animated:YES completion:^{
            NSLog(@"call back");
        }];
    }
}

-(void)textChange:(NSString *)text
{
    _textField.text = text;
}
@end
