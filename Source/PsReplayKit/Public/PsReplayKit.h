// Copyright 2016 Mail.Ru Group. All Rights Reserved.

#pragma once

//#include "PsReplayKitPrivatePCH.h"
#include "Modules/ModuleManager.h"
#include "PsReplayKitClasses.h"

DECLARE_LOG_CATEGORY_EXTERN(LogReplayKit, Display, All);

class IPsReplayKitModule : public IModuleInterface
{

public:
	/**
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline IPsReplayKitModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IPsReplayKitModule>("PsReplayKit");
	}
	
	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("PsReplayKit");
	}
};
