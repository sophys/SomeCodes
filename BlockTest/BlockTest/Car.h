//
//  Car.h
//  BlockTest
//
//  Created by Ysan on 14-4-3.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import <Foundation/Foundation.h>
typedef double (^speedFuntion)(double);

@interface Car : NSObject
@property double odometer;
-(void)driveForDuration:(double)duration
      withVariableSpeed:(double (^)(double time))speedFuntion
                  steps:(int)numSteps;

@end
