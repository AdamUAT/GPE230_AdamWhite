// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "LockAndKey.generated.h"

/**
 * 
 */
UCLASS()
class GPE230_ADAMWHITE_API ALockAndKey : public ATriggerBox
{
	GENERATED_BODY()
public:
	ALockAndKey();

	UFUNCTION()
		void CheckActorType(class AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void OpenTheDoor();
};
