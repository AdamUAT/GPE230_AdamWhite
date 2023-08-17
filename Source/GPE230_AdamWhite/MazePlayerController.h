// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
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
	virtual void BeginPlay() override;

	bool isDead = false;
protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> _gameOverScreenTemplate;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> _victoryScreenTemplate;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> _pauseScreenTemplate;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> _hudScreenTemplate;
	bool isPaused = false;
public:
	UUserWidget* _gameOverScreenInstance;
	UUserWidget* _victoryScreenInstance;
	UUserWidget* _pauseScreenInstance;
	UUserWidget* _hudScreenInstance;
	UFUNCTION(BlueprintCallable)
		virtual void OpenVictoryScreen();
	virtual void OpenGameOverScreen();
	UFUNCTION(BlueprintCallable)
		virtual void TogglePauseGameplay();
};
