// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeCharacter.h"
#include "Pickup.h"

// Sets default values
APickup::APickup()
{
	OnActorBeginOverlap.AddDynamic(this, &APickup::CheckActorType);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickup::CheckActorType(class AActor* OverlappedActor, AActor* OtherActor)
{
	//Only run if the entered actor was the player.
	if (OtherActor->IsA(AMazeCharacter::StaticClass()))
	{
		//Call the 
		OnPickup(OtherActor);
	}
}

void APickup::OnPickup_Implementation(AActor* player)
{
	UE_LOG(LogTemp, Log, TEXT("Not implemented pickup."));
}

