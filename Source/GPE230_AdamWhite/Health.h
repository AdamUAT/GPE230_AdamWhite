// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GPE230_ADAMWHITE_API UHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealth();
	UPROPERTY(EditAnywhere)
	float maxHealth;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float currentHealth;

public:	
	UFUNCTION(BlueprintCallable)
	virtual void TakeDamage(float DamageAmount);
	UFUNCTION(BlueprintCallable)
	virtual void Heal(float healthAmount);
	virtual void Die();
	//Test function
	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth();
private:
	UPROPERTY(EditAnywhere)
		UAnimSequence* _deathAnim;
	UPROPERTY(EditAnywhere)
		bool _isDead = false;
};
