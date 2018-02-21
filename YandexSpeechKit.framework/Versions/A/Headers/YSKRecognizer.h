//
// YSKRecognizer.h
//
// This file is a part of the Yandex SpeechKit project.
//
// (C) Copyright 2013 Yandex, LLC. All rights reserved.
//
// Author: Sergey Zimin <szimin@yandex-team.ru>
//

#import <Foundation/Foundation.h>

/*!
    @defgroup recognizer_globals_group Global YSKRecognizer constants
    Constants for use in YSKRecognizer initialization: possible language models and recognition languages.
 */

/// Recognition model for buying.
extern NSString *const YSKRecognitionModelBuying;

/// Recognition model for dates.
extern NSString *const YSKRecognitionModelDates;

/*!
 @ingroup recognizer_globals_group
 @brief %Recognition model for regular speech.
 @details This is a model for text dictation and suitable for dictating mail, SMS and so on. This model is sensitive to words completions and arranges punctuation.
 */
extern NSString *const YSKRecognitionModelFreeform;

/*!
    @ingroup recognizer_globals_group
    @brief %Recognition model, based on usual search requests.
 */
extern NSString *const YSKRecognitionModelGeneral;

/*!
 @ingroup recognizer_globals_group
 @brief %Recognition model for geographical names, adresses, organization names.
 */
extern NSString *const YSKRecognitionModelMaps;

/*!
    @ingroup recognizer_globals_group
    @brief %Recognition model for music.
    @details You can recognize both music and speech using this model. SpeechKit backend makes two parallel requests to different recognition systems in this case.
 */
extern NSString *const YSKRecognitionModelMusic;

/// Recognition model for names.
extern NSString *const YSKRecognitionModelNames;

/// Recogniton model for notes.
extern NSString *const YSKRecognitionModelNotes;

/// Recognition model for numbers.
extern NSString *const YSKRecognitionModelNumbers;

/// Recogntion model for queries.
extern NSString *const YSKRecognitionModelQueries;


/*!
    @ingroup recognizer_globals_group
    @brief Value for recognition language, specified in BCP 47 format (http://en.wikipedia.org/wiki/IETF_language_tag).
 */
//@{
extern NSString *const YSKRecognitionLanguageEnglish;
extern NSString *const YSKRecognitionLanguageRussian;
extern NSString *const YSKRecognitionLanguageTurkish;
extern NSString *const YSKRecognitionLanguageUkrainian;
//@}


@protocol YSKRecognizerDelegate;

/*!
    @interface YSKRecognizer
    @brief The interface to a single-use Recognizer.
    @details The {@link YSKRecognizer} object manages the entire recognition process including audio recording, voice activity detection, server communication, and so on.

    Recognizer is designed to carry out a single recognition and may not be reused. Subsequent recognitions should each be generated by creating a new {@link YSKRecognizer} object.

    The recognizer notifies via {@link YSKRecognizerDelegate} interface about important events in the recognition process.

    @note SpeechKit shall be initialized via {@link YSKSpeechKit::configureWithAPIKey:} before creating any recognizer.

    @note The {@link YSKRecognizer} object may be created even before the initialization has been performed ({@link YSKInitializer}). In this case, the recognizer will initiate the initializer internally before the actual recognition.

    @note The recognizer initializes and holds several mutual resources, so two instances of the {@link YSKRecognizer} class may not co-exist. A new {@link YSKRecognizer} object may be created only after the current recognition is finished with either {@link YSKRecognizerDelegate::recognizer:didFailWithError:} or {@link YSKRecognizerDelegate::recognizer:didCompleteWithResults:} method invocation.
 */
@interface YSKRecognizer : NSObject

/*!
    @property delegate
    @brief The delegate object for the recognizer callbacks.
    @details The delegate will receive notifications when recording starts and finishes, when the recognition result is received, and when an error occurs.
 */
@property(nonatomic, weak) id<YSKRecognizerDelegate> delegate;

/*!
    @brief Initializes a single-use {@link YSKRecognizer} object.

    @details You can find possible values in @ref recognizer_globals_group.
             Call the {@link start} method to begin the recognition.
             @note Don't forget to set {@link YSKRecognizer::delegate} property.

    @param language the language spoken by the user, specified in BCP 47 format (http://en.wikipedia.org/wiki/IETF_language_tag). BCP 47 expresses the language as an ISO 639 language code, followed by a dash "-", followed by the ISO 3166-1 country code. For example, an English speaker from the United States would be expressed as "en-US". Possible values declared in section "Public Attributes".
    @param model the language model to be used for recognition. This allows the server to better anticipate the type of phrases the user is likely to say and select an appropriate vocabulary of words that the user might say, and therefore has an impact on recognition accuracy. Possible values declared in section "Public Attributes".
    @return The {@link YSKRecognizer} object corresponding to the recognition request.
 */
- (instancetype)initWithLanguage:(NSString *)language model:(NSString *)model;

/*!
    @brief Initializes a single-use {@link YSKRecognizer} object.
*/
- (instancetype)initWithLanguage:(NSString *)language model:(NSString *)model continuousMode:(BOOL)continuousMode;

/*!
    @brief Release the resources used by the {@link YSKRecognizer} object.
 */
- (void)dealloc;

/*!
    @brief Checks whether the recognition is currently available.
    @note If the initialization has not been completed, the function always returns YES.
 */
+ (BOOL)isRecognitionAvailable;

/*!
    @brief Starts the recognition process.
    @details It might take time to initialize the audio device and establish a connection to the speech server. This means the recording will not start immediately after the function is invoked. When recording actually starts, the {@link YSKRecognizerDelegate::recognizerDidStartRecording:} method is called.
 */
- (void)start;

/*!
    @brief Force finish sound recording and complete the request out.
    @details Normally this method should not be invoked, because Voice Activity Detector (VAD) detects the end of speech automatically. However, this method is needed when VAD is disabled or it does not detect the end of speech properly.
 */
- (void)finishRecording;

/*!
    @brief Cancels the recognition request.
    @details The method cancels the recognition request at any stage of the operation. The audio recording stops and network communication breaks if needed.
    @note The function cancels the request asynchronously. This means that the recognition is not cancelled immediately after invoking this function and it still might invoke callbacks.
    @note The recognizer will be destroied automatically when either {@link YSKRecognizerDelegate::recognizer:didFailWithError:} or {@link YSKRecognizerDelegate::recognizer:didCompleteWithResults:} method is invoked.
 */
- (void)cancel;

/*!
    @brief Stop voice recording without interrupting a session
    @details Allows temporary send silence instead of recorded audio to service without stopping recognition session.
    @see unmute()
 */
- (void)mute;

/*!
    @brief Resume voice recording of muted session
    @details Allows to unmute audio input, muted by {@link mute()}.
    @see mute()
 */
- (void)unmute;

/*!
    @property language
    @brief The language of the recognition request.
 */
@property (nonatomic, assign, readonly, getter=getLanguge) NSString* language;

/*!
    @property model
    @brief The model of the recognition request.
 */
@property (nonatomic, assign, readonly, getter=getModel) NSString* model;

/*!
    @property VADEnabled
    @brief Controls the behavior of the Voice Activity Detector (VAD).
    @details If VAD is disabled, SpeechKit will not detect the end of an utterance automatically. In this case, call {@link finishRecording:} to finish the recording and proceed with the recognition.
 */
@property (nonatomic, assign, readwrite, getter=isVADEnabled) BOOL VADEnabled;

@end
