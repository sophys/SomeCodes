//
//  Observer.m
//  FileCopyKVO
//
//  Created by Ysan on 14-4-3.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import "Observer.h"

@implementation Observer
-(id)init{
    if([super init])
    {
        NSString * dir = NSHomeDirectory();
        NSLog(@"------%@-----",dir);
        NSString *srcPath = [dir stringByAppendingPathComponent:@"a.out"];
        NSString *desPath = [dir stringByAppendingPathComponent:@"a_bak.out"];
        
        file = [[FileHandler alloc] initPath:srcPath desPath:desPath];
           [file addObserver:self forKeyPath:@"readsize" options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld context:nil];
    }
    return self;
}

-(void)copy
{
    [file startCopy];
}
-(void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
    if ([keyPath isEqualToString:@"readsize"]) {
        NSNumber *readsizeNum = [change objectForKey:@"new"];
        float readsize = [readsizeNum floatValue];

        if ([object isKindOfClass:[FileHandler class]]) {
            FileHandler *file1 = (FileHandler *)object;
            float filesize = file1.size;
            float result = readsize/filesize * 100;
            NSLog(@"======%0.1f%%=======",result);
        }

    }
}

-(void)dealloc
{
    [file removeObserver:self forKeyPath:@"readsize"];
}
@end
