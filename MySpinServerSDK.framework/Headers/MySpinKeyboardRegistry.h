//
//  MySpinKeyboardRegister.h
//  AppSDK
//
//  mySPIN.SDK Version: 2.3.3.110
//
//  Created by Yufei Zhu on 01.07.14.
//  Copyright (c) 2014 Bosch SoftTec GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MySpinKeyboardProtocol.h"

#ifndef __MYSPINKEYBOARDREGISTER_H__
#define __MYSPINKEYBOARDREGISTER_H__

@interface MySpinKeyboardRegistry : NSObject

/**
 Access the singleton instance to add or remove keyboards.
 */
+ (nonnull MySpinKeyboardRegistry*)sharedInstance;


/**
Register an external keyboard

@param extKeyboard Keyboard class that implements MySpinKeyboardProtocol
*/
- (void)registerExternalKeyboardClass:(Class _Nonnull)extKeyboard;

@end

#endif

