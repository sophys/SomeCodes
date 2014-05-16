//
//  Car.m
//  BlockTest
//
//  Created by Ysan on 14-4-3.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import "Car.h"

@implementation Car
@synthesize odometer=_odometer;

-(void)driveForDuration:(double)duration withVariableSpeed:(speedFuntion)speedFuntion steps:(int)numSteps{
    double dt = duration/numSteps;
    for (int i = 0; i<numSteps; i++) {
        _odometer += speedFuntion(i*dt)*dt;
    }
}
@end
