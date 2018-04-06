// Copyright 2016 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "PsReplayKitPrivatePCH.h"

#if WITH_REPLAYKIT

#import <ReplayKit/ReplayKit.h>
#import <UIKit/UIKit.h>

@interface PsReplayKitDelegate : NSObject <RPPreviewViewControllerDelegate, RPScreenRecorderDelegate, RPBroadcastActivityViewControllerDelegate, RPBroadcastControllerDelegate>

@property (nonatomic, retain) RPBroadcastController* streamController;

+ (instancetype)sharedInstance;

- (void)StartRecording;
- (void)StopRecording;

- (void)StartStreaming;
- (void)StopStreaming;

- (bool)IsAvailable;
- (bool)IsRecording;

// RPScreenRecorderDelegate
- (void)screenRecorder:(RPScreenRecorder *)screenRecorder didStopRecordingWithError:(NSError *)error previewViewController:(RPPreviewViewController *)previewViewController;
- (void)screenRecorder:(RPScreenRecorder *)screenRecorder didStopRecordingWithPreviewViewController:(RPPreviewViewController *)previewViewController error:(NSError *)error;
- (void)screenRecorderDidChangeAvailability:(RPScreenRecorder *)screenRecorder;

// RPPreviewViewControllerDelegate
- (void)previewControllerDidFinish:(RPPreviewViewController *)previewController;
- (void)previewController:(RPPreviewViewController *)previewController didFinishWithActivityTypes:(NSSet<NSString *> *)activityTypes;

@end

#endif
