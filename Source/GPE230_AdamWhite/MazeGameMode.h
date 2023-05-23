// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/DefaultPawn.h"
#include "MazeCharacter.h"

#include "MazeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GPE230_ADAMWHITE_API AMazeGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void InitGameState() override;

private:
	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<AMazeCharacter> DefaultPlayerCharacter = AMazeCharacter::StaticClass();
};
