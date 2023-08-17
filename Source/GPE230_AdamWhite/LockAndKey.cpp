// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeCharacter.h"
#include "LockAndKey.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"

ALockAndKey::ALockAndKey()
{
	OnActorBeginOverlap.AddDynamic(this, &ALockAndKey::CheckActorType);
}

void ALockAndKey::CheckActorType(class AActor* OverlappedActor, AActor* OtherActor)
{
	//Only run if the entered actor was the player.
	if (OtherActor->IsA(AMazeCharacter::StaticClass()))
	{
		OpenTheDoor();
	}
}

void ALockAndKey::OpenTheDoor()
{
	this->Destroy();
	for (int i = 0; i < doorsToUnlock.Num(); i++)
	{
		doorsToUnlock[i]->Destroy();
	}

	//Play sound
	UGameplayStatics::PlaySound2D(this, _doorSound);
}
