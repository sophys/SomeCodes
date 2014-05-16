//
//  FileHandler.m
//  FileCopyKVO
//
//  Created by Ysan on 14-4-3.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import "FileHandler.h"

@implementation FileHandler
@synthesize size;


-(id)initPath:(NSString *)srcPath desPath:(NSString *)desPath
{
    if([super init]){
        _srcPath=[srcPath copy];
        _desPath=[desPath copy];
    }
    return self;
}

-(void)startCopy
{
    NSFileManager *manager = [NSFileManager defaultManager];
    if ([manager createFileAtPath:_desPath contents:nil attributes:nil])
    {
        NSLog(@"Create file success");
    }
    
    NSFileHandle *read = [NSFileHandle fileHandleForReadingAtPath:_srcPath];
    NSFileHandle *write = [NSFileHandle fileHandleForWritingAtPath:_desPath];
    
    NSDictionary  *fileAttr = [manager attributesOfItemAtPath:_srcPath error:nil];
    size = [[fileAttr objectForKey:NSFileSize] longValue];
    BOOL isEnd = YES;
    while (isEnd)
    {
        NSInteger subLong = size - self.readsize;
        NSData *data=nil;
        if (subLong < 5000)
        {
            isEnd = NO;
            data= [read readDataToEndOfFile];
            self.readsize=size;
        }
        else
        {
            self.readsize += 5000;
            data = [read readDataOfLength:5000];
            [read seekToFileOffset:self.readsize];
        }
        [write writeData:data];
    }
    
    [read closeFile];
    [write closeFile];
}

@end
