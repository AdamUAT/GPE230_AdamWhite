// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MazePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GPE230_ADAMWHITE_API AMazePlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	void MoveFB(float value);
	void MoveLR(float value);
	void Rotate(float value);
	void Stun();
public:
	//Called to bind input to functions
	virtual void SetupInputComponent() override;

	bool isDead = false;
};
