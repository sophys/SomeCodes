//
//  FileHandler.h
//  FileCopyKVO
//
//  Created by Ysan on 14-4-3.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FileHandler : NSObject
{
    @private
    NSString* _srcPath;
    NSString* _desPath;
}
@property(nonatomic,assign)float size;
@property(nonatomic,assign)float readsize;

-(id)initPath:(NSString*)srcPath desPath:(NSString*)desPath;
-(void)startCopy;
@end
