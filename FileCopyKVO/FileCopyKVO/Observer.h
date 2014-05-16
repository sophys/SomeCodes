//
//  Observer.h
//  FileCopyKVO
//
//  Created by Ysan on 14-4-3.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FileHandler.h"
@interface Observer : NSObject{
    FileHandler *file;
}

-(void)copy;
@end
