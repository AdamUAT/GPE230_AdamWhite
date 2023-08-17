// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGameMode.h"
#include "MazePlayerController.h"

void AMazeGameMode::InitGameState()
{
	Super::InitGameState();

	if (DefaultPawnClass == ADefaultPawn::StaticClass())
	{
		DefaultPawnClass = DefaultPlayerCharacter;
	}

	//Check if the player controller is set to a default, then make it the maze controller.
	if (PlayerControllerClass == APlayerController::StaticClass())
	{
		PlayerControllerClass = AMazePlayerController::StaticClass();
	}
}
