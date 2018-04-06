// Fill out your copyright notice in the Description page of Project Settings.
#include "PsReplayKitPrivatePCH.h"
#include "PsReplayKitTool.h"

#if WITH_REPLAYKIT
	#include "IOS/PsReplayKitDelegate.h"
#endif

void UPsReplayKitTool::StartRecording()
{
#if WITH_REPLAYKIT
	dispatch_async(dispatch_get_main_queue(), ^{
		[[PsReplayKitDelegate sharedInstance] StartRecording];
	});
#endif
}

void UPsReplayKitTool::StopRecording()
{
#if WITH_REPLAYKIT
	dispatch_async(dispatch_get_main_queue(), ^{
		[[PsReplayKitDelegate sharedInstance] StopRecording];
	});
#endif
}

void UPsReplayKitTool::StartStreaming()
{
#if WITH_REPLAYKIT
	dispatch_async(dispatch_get_main_queue(), ^{
		[[PsReplayKitDelegate sharedInstance] StartStreaming];
	});
#endif
}

void UPsReplayKitTool::StopStreaming()
{
#if WITH_REPLAYKIT
	dispatch_async(dispatch_get_main_queue(), ^{
		[[PsReplayKitDelegate sharedInstance] StopStreaming];
	});
#endif
}

bool UPsReplayKitTool::IsAvailable()
{
	#if WITH_REPLAYKIT
		return [[PsReplayKitDelegate sharedInstance] IsAvailable];
	#endif
	
	return false;
}

bool UPsReplayKitTool::IsRecording()
{
#if WITH_REPLAYKIT
	return [[PsReplayKitDelegate sharedInstance] IsRecording];
#endif
	
	return false;
}
