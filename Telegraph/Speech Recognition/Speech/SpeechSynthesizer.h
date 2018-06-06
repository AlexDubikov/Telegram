//
//  SpeechSynthesizer.h
//  SpeechRecognition
//
//  Created by Ilya Tsarev on 22.04.2018.
//  Copyright © 2018 Ilya Tsarev. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SpeechSynthesizer : NSObject

- (instancetype)initWithLocale:(NSString *)locale;
- (instancetype)initWithLocale:(NSString *)locale speechRate:(float)speechRate;
- (void)synthesizeText:(NSString *)text;

@end
