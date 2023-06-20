// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

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
	if (DamageAmount > 0)
	{
		currentHealth -= DamageAmount;

		if (currentHealth <= 0)
		{
			Die();
		}
	}
}

void UHealth::Die()
{
	//Do die stuff later.
}

float UHealth::GetCurrentHealth()
{
	return currentHealth;
}

