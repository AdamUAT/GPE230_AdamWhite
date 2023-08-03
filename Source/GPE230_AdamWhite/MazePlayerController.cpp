// Fill out your copyright notice in the Description page of Project Settings.


#include "MazePlayerController.h"
#include "MazeCharacter.h"

void AMazePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MoveFB"), this, &AMazePlayerController::MoveFB);
	InputComponent->BindAxis(TEXT("MoveLR"), this, &AMazePlayerController::MoveLR);
	InputComponent->BindAxis(TEXT("Rotate"), this, &AMazePlayerController::Rotate);
	InputComponent->BindAction("Stun", IE_Pressed, this, &AMazePlayerController::Stun);
}

void AMazePlayerController::MoveFB(float value)
{
	if (!isDead)
	{
		if (AMazeCharacter* mazePawn = Cast<AMazeCharacter>(GetPawn()))
		{
			mazePawn->MoveFB(value);
		}
	}
}

void AMazePlayerController::MoveLR(float value)
{
	if (!isDead)
	{
		if (AMazeCharacter* mazePawn = Cast<AMazeCharacter>(GetPawn()))
		{
			mazePawn->MoveLR(value);
		}
	}
}

void AMazePlayerController::Rotate(float value)
{
	if (!isDead)
	{
		if (AMazeCharacter* mazePawn = Cast<AMazeCharacter>(GetPawn()))
		{
			mazePawn->Rotate(value);
		}
	}
}

void AMazePlayerController::Stun()
{
	if (!isDead)
	{
		if (AMazeCharacter* mazePawn = Cast<AMazeCharacter>(GetPawn()))
		{
			mazePawn->Stun();
		}
	}
}