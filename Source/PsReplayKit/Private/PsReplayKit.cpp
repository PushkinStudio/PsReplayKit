// Copyright 2016 Mail.Ru Group. All Rights Reserved.

#include "PsReplayKitPrivatePCH.h"
#include "PsReplayKit.h"

#define LOCTEXT_NAMESPACE "FPsReplayKitModule"

DEFINE_LOG_CATEGORY(LogReplayKit)

class FPsReplayKitModule : public IPsReplayKitModule
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override
	{
		UE_LOG(LogReplayKit, Warning, TEXT("REPLAYKIT LOADED"));
	}

	virtual void ShutdownModule() override
	{

	}
};

IMPLEMENT_MODULE(FPsReplayKitModule, PsReplayKit)
