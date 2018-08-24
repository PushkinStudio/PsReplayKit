// Copyright 2016 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "Runtime/Launch/Resources/Version.h"

#if ENGINE_MINOR_VERSION >= 15
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/ScriptMacros.h"
#else
#include "CoreUObject.h"
#include "Engine.h"
#include "Core.h"
#endif

#if WITH_REPLAYKIT
	#include <iostream>
	#include "IOS/PsReplayKitDelegate.h"
#endif

#include "Modules/ModuleManager.h"
#include "PsReplayKitClasses.h"
#include "PsReplayKit.h"
