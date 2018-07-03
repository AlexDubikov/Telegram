//
//  SpeechRecognizer.h
//  SpeechRecognition
//
//  Created by Ilya Tsarev on 18.04.2018.
//  Copyright © 2018 Ilya Tsarev. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SpeechRecognizer : NSObject

- (instancetype)initWithLocale:(NSLocale *)locale;

- (void)startRecognition:(void (^) (NSString *recognizedString, BOOL isFinal))partialCompletion;
- (void)requestAuthorization:(void (^) (BOOL isAuthorized))completion;
- (void)stopRecognition;
@end
