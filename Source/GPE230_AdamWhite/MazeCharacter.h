// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NiagaraComponent.h"
#include "MazeCharacter.generated.h"

UCLASS()
class GPE230_ADAMWHITE_API AMazeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMazeCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
		float moveSpeed;
	UPROPERTY(EditAnywhere)
		float rotationSpeed;
	UPROPERTY(EditAnywhere)
		float stunCooldownDelay;
	float currentStunCooldown;
	UPROPERTY(EditAnywhere)
		UNiagaraSystem* StunEffect;
	UPROPERTY(EditAnywhere)
		float StunRadius;

private:
	void MoveFB(float value);
	void MoveLR(float value);
	void Rotate(float value);
	void Stun();

public:
	UFUNCTION(BlueprintCallable)
		void SpeedBoost(float amount);
};
