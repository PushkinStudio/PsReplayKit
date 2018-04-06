// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "PsReplayKit.h"
#include "PsReplayKitTool.generated.h"

UCLASS(BlueprintType)
class PSREPLAYKIT_API UPsReplayKitTool : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "PsReplayKit|Actions")
	void StartRecording();
	
	UFUNCTION(BlueprintCallable, Category = "PsReplayKit|Actions")
	void StopRecording();
	
	UFUNCTION(BlueprintCallable, Category = "PsReplayKit|Actions")
	bool IsAvailable();
	
	UFUNCTION(BlueprintCallable, Category = "PsReplayKit|Actions")
	bool IsRecording();
	
	UFUNCTION(BlueprintCallable, Category = "PsReplayKit|Actions")
	void StartStreaming();
	
	UFUNCTION(BlueprintCallable, Category = "PsReplayKit|Actions")
	void StopStreaming();
	
};
