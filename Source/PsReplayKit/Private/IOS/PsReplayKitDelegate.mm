// Copyright 2016 Mail.Ru Group. All Rights Reserved.

#include "PsReplayKitPrivatePCH.h"

#if WITH_REPLAYKIT

#import "IOS/PsReplayKitDelegate.h"

using namespace std;

@implementation PsReplayKitDelegate

@synthesize streamController;

+ (instancetype)sharedInstance
{
	static PsReplayKitDelegate * sharedInstance = nil;
	static dispatch_once_t onceToken;
	dispatch_once(&onceToken, ^{
		sharedInstance = [[PsReplayKitDelegate alloc] init];
	});
	return sharedInstance;
}

/** Recording */

- (void)StartRecording
{
	RPScreenRecorder *sharedRecorder = RPScreenRecorder.sharedRecorder;
	if (sharedRecorder) {
		sharedRecorder.delegate = self;
		if ([sharedRecorder respondsToSelector:@selector(startRecordingWithHandler:)]) {
			// iOS 10+
			[sharedRecorder startRecordingWithHandler:^(NSError *error) {
				if (error) {
					NSLog(@"startScreenRecording: %@", error.localizedDescription);
				}
			}];
		}
		else
		{
			// pre-iOS 10
			[sharedRecorder startRecordingWithMicrophoneEnabled:YES handler:^(NSError *error) {
				if (error) {
					NSLog(@"startScreenRecording: %@", error.localizedDescription);
				}
			}];
		}
	}
}

- (void)StopRecording
{
	RPScreenRecorder *sharedRecorder = RPScreenRecorder.sharedRecorder;
	if (sharedRecorder) {
		[sharedRecorder stopRecordingWithHandler:^(RPPreviewViewController *previewViewController, NSError *error) {
			if (error) {
				NSLog(@"stopScreenRecording: %@", error.localizedDescription);
			}

			if (previewViewController) {
				previewViewController.previewControllerDelegate = self;

				previewViewController.modalPresentationStyle = UIModalPresentationFullScreen;

				[[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:previewViewController animated:YES completion:nil];
			}
		}];
	}
}

- (bool)IsAvailable
{
	RPScreenRecorder* sharedRecorder = RPScreenRecorder.sharedRecorder;
	if (sharedRecorder)
	{
		return sharedRecorder.available;
	}

	return false;
}

- (bool)IsRecording
{
	RPScreenRecorder* sharedRecorder = RPScreenRecorder.sharedRecorder;
	if (sharedRecorder)
	{
		return sharedRecorder.recording;
	}

	return false;
}

- (void)screenRecorder:(RPScreenRecorder *)screenRecorder didStopRecordingWithError:(NSError *)error previewViewController:(nullable RPPreviewViewController *)previewViewController
{
	NSLog(@"didStopRecordingWithError");
	// deprecated
}

- (void)screenRecorder:(RPScreenRecorder *)screenRecorder didStopRecordingWithPreviewViewController:(RPPreviewViewController *)previewViewController error:(NSError *)error
{
	NSLog(@"didStopRecordingWithPreviewViewController");
	// iOS 11+
}

- (void)screenRecorderDidChangeAvailability:(RPScreenRecorder *)screenRecorder
{
	NSLog(@"screenRecorderDidChangeAvailability");
	// handle screen recorder availability changes
}

- (void)previewControllerDidFinish:(RPPreviewViewController *)previewController
{
	NSLog(@"previewControllerDidFinish");
	[previewController dismissViewControllerAnimated:YES completion:nil];
}

- (void)previewController:(RPPreviewViewController *)previewController didFinishWithActivityTypes:(NSSet<NSString *> *)activityTypes
{
	NSLog(@"previewController: didFinishWithActivityTypes:");
	[previewController dismissViewControllerAnimated:YES completion:nil];
}

/** Streaming*/

- (void)StartStreaming
{
	if (streamController == nil) {
		if ([RPBroadcastActivityViewController class]) {
			[RPBroadcastActivityViewController loadBroadcastActivityViewControllerWithHandler:^(RPBroadcastActivityViewController* _Nullable broadcastActivityViewController, NSError* _Nullable error) {

				if ([UIApplication sharedApplication].keyWindow && [UIApplication sharedApplication].keyWindow.rootViewController)
				{
					UIView* rootView = [UIApplication sharedApplication].keyWindow.rootViewController.view;
					if (rootView)
					{
						broadcastActivityViewController.delegate = self;
						broadcastActivityViewController.modalPresentationStyle = UIModalPresentationPopover;
						broadcastActivityViewController.popoverPresentationController.sourceView = rootView;
						broadcastActivityViewController.popoverPresentationController.sourceRect = rootView.frame;

						[[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:broadcastActivityViewController animated:YES completion:nil];
					}
				}
			}];
		}
	}
}


- (void)StopStreaming
{
	if (streamController && streamController.broadcasting) {
		[streamController finishBroadcastWithHandler:^(NSError * _Nullable error) {
			if(error) {
				NSLog(@"PsReplayKit: %@", [error localizedDescription]);
			}
			NSLog(@"PsReplayKit: finishBroadcastWithHandler");
		}];

		streamController = nil;
	}
}

- (void)broadcastActivityViewController:(RPBroadcastActivityViewController *)broadcastActivityViewController didFinishWithBroadcastController:(nullable RPBroadcastController *)broadcastController error:(nullable NSError *)error
{
	[broadcastActivityViewController dismissViewControllerAnimated:YES completion:^() {
		 NSLog(@"PsReplayKit: broadcastActivityViewController dismissViewControllerAnimated");
	}];
	if (broadcastController) {
		streamController = broadcastController;
		streamController.delegate = self;
		[streamController startBroadcastWithHandler:^(NSError * _Nullable errorBroadcast) {
			 if (errorBroadcast) {
				 NSLog(@"PsReplayKit: %@", [errorBroadcast localizedDescription]);
			 }
			 NSLog(@"PsReplayKit: startBroadcastWithHandler");
		 }];
	}
}

- (void)broadcastController:(RPBroadcastController *)broadcastController didFinishWithError:(NSError *)error
{
	if (error) {
		NSLog(@"PsReplayKit: %@",[error localizedDescription]);
	}
	NSLog(@"PsReplayKit: didFinishWithError");
	if (streamController) {
		streamController = nil;
	}
}

@end

#endif
