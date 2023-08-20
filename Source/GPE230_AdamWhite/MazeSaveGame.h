// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MazeSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class GPE230_ADAMWHITE_API UMazeSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		int furthestCompletedLevel;
	UPROPERTY(BlueprintReadWrite)
		float masterVolumeSetting;
	UPROPERTY(BlueprintReadWrite)
		float musicVolumeSetting;
	UPROPERTY(BlueprintReadWrite)
		float sfxVolumeSetting;
};