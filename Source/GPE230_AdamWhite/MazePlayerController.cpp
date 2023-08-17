// Fill out your copyright notice in the Description page of Project Settings.


#include "MazePlayerController.h"
#include "Blueprint/UserWidget.h"
#include "MazeCharacter.h"

void AMazePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MoveFB"), this, &AMazePlayerController::MoveFB);
	InputComponent->BindAxis(TEXT("MoveLR"), this, &AMazePlayerController::MoveLR);
	InputComponent->BindAxis(TEXT("Rotate"), this, &AMazePlayerController::Rotate);
	InputComponent->BindAction("Stun", IE_Pressed, this, &AMazePlayerController::Stun);
	InputComponent->BindAction("Pause", IE_Pressed, this, &AMazePlayerController::TogglePauseGameplay);
}

void AMazePlayerController::BeginPlay()
{
	Super::BeginPlay();

	_gameOverScreenInstance = CreateWidget(GetWorld(), _gameOverScreenTemplate);
	_victoryScreenInstance = CreateWidget(GetWorld(), _victoryScreenTemplate);
	_pauseScreenInstance = CreateWidget(GetWorld(), _pauseScreenTemplate);
	_hudScreenInstance = CreateWidget(GetWorld(), _hudScreenTemplate);
	_pauseScreenInstance->AddToViewport();
	_pauseScreenInstance->SetVisibility(ESlateVisibility::Hidden);
	_hudScreenInstance->AddToViewport();
	_hudScreenInstance->SetVisibility(ESlateVisibility::Visible);
	isPaused = false;
}

void AMazePlayerController::OpenGameOverScreen()
{
	_gameOverScreenInstance->AddToViewport();
	SetPause(true);
	bShowMouseCursor = true;
	isPaused = true;

	//Use this bool to make the player unable to unpause the game and move around.
	isDead = true;
}

void AMazePlayerController::TogglePauseGameplay()
{
	isPaused = !isPaused;
	SetPause(isPaused);
	bShowMouseCursor = isPaused;
	if (isPaused)
	{
		_pauseScreenInstance->SetVisibility(ESlateVisibility::Visible);
		_hudScreenInstance->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		_pauseScreenInstance->SetVisibility(ESlateVisibility::Hidden);
		_hudScreenInstance->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMazePlayerController::OpenVictoryScreen()
{
	_victoryScreenInstance->AddToViewport();
	SetPause(true);
	bShowMouseCursor = true;
	isPaused = true;
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