// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"
#include "GameFramework/Character.h"
#include "MazePlayerController.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	//Sets the value of currentHealth to maxHealth.
	currentHealth = maxHealth;
}

void UHealth::TakeDamage(float DamageAmount)
{
	if (DamageAmount > 0 && !_isDead)
	{
		currentHealth -= DamageAmount;

		UE_LOG(LogTemp, Log, TEXT("Player took %f damage. %f health remaining."), DamageAmount, currentHealth);

		if (currentHealth <= 0)
		{
			currentHealth = 0;
			Die();
		}
	}
}

void UHealth::Heal(float healthAmount)
{
	if (healthAmount > 0 && !_isDead)
	{
		currentHealth += healthAmount;

		if (currentHealth > maxHealth)
		{
			currentHealth = maxHealth;
		}

		UE_LOG(LogTemp, Log, TEXT("Player healed %f damage. %f health remaining."), healthAmount, currentHealth);

	}
}

void UHealth::Die()
{
	_isDead = true;

	if (ACharacter* componentOwner = Cast<ACharacter>(GetOwner()))
	{
		componentOwner->GetMesh()->PlayAnimation(_deathAnim, false);

		if (APlayerController* playerController = Cast<APlayerController>(componentOwner->GetController()))
		{
			if (AMazePlayerController* mazePlayerController = Cast<AMazePlayerController>(playerController))
			{
				mazePlayerController->isDead = true;
			}
		}
	}

	//Get the mesh from the character attached to this component and play the death animation on it.
	Cast<ACharacter>(GetOwner())->GetMesh()->PlayAnimation(_deathAnim, false);
}

