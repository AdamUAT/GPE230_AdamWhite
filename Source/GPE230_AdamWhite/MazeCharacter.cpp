// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Stunnable.h"
#include "Sound/SoundWave.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Rotator.h"
#include "Engine/World.h"

// Sets default values
AMazeCharacter::AMazeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMazeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	currentStunCooldown = stunCooldownDelay;

	TArray<USpringArmComponent*> CameraComps;
	GetComponents<USpringArmComponent>(CameraComps);

	if (CameraComps.Num() > 0)
	{
		_cameraReference = CameraComps[0];
	}
}

// Called every frame
void AMazeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Decrease the stun cooldown
	if (currentStunCooldown > 0)
	{
		currentStunCooldown -= DeltaTime;
	}
}

void AMazeCharacter::MoveFB(float value)
{
	AddMovementInput(GetActorForwardVector(), value * moveSpeed);
}

void AMazeCharacter::MoveLR(float value)
{
	AddMovementInput(-GetActorRightVector(), value * moveSpeed);
}

void AMazeCharacter::Rotate(float value)
{
	AddControllerYawInput(value * rotationSpeed);

	if (_cameraReference != nullptr)
	{
		FRotator rollRotation(0, 0, cameraRollSpeed * value * GetWorld()->GetDeltaSeconds());
		_cameraReference->SetWorldRotation(_cameraReference->GetComponentRotation() + rollRotation);
		if (_cameraReference->GetComponentRotation().Roll > maxCameraRoll)
		{
			_cameraReference->SetWorldRotation(FRotator(_cameraReference->GetComponentRotation().Pitch, _cameraReference->GetComponentRotation().Yaw, maxCameraRoll));
		}
		else if (_cameraReference->GetComponentRotation().Roll < minCameraRoll)
		{
			_cameraReference->SetWorldRotation(FRotator(_cameraReference->GetComponentRotation().Pitch, _cameraReference->GetComponentRotation().Yaw, minCameraRoll));
		}
		//_cameraReference->AddLocalRotation(FQuat::MakeFromEuler(FVector::UnitX()) * cameraRollSpeed * value * GetWorld()->GetDeltaSeconds());
	}
}

void AMazeCharacter::Stun()
{
	UE_LOG(LogTemp, Log, TEXT("Stun called"));

	//Check if the player can stun
	if (currentStunCooldown <= 0)
	{
		//Set the stun cooldown.
		currentStunCooldown = stunCooldownDelay;

		//Display visuals
		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(StunEffect, GetDefaultAttachComponent(), NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
		
		//Play sound
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), _stunSound, this->GetActorLocation());

		TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
		objectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
		TArray<AActor*> outActors;
		TArray<AActor*> actorsToIgnore;
		//Ignore the player actor
		actorsToIgnore.Add(GetOwner());
		UClass* componentFilter = UStunnable::StaticClass();
		bool hit = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), this->GetActorLocation(), StunRadius, objectTypes, nullptr, actorsToIgnore, outActors);
	
		//Detect if at least one component was found.
		if (hit)
		{
			//Loop through all the actors
			for (int i = 0; i < outActors.Num(); i++)
			{
				//Get the Stunnable component. This only stuns actors with that component.
				TArray<UStunnable*> stunComps;
				outActors[i]->GetComponents(stunComps);

				//Detect if there was a stunnable component
				if (stunComps.Num() > 0)
				{
					//Call the function.
					stunComps[0]->Stunned();
				}
			}
		}
	}
}

float AMazeCharacter::GetStunPercentFull()
{
	float temp = currentStunCooldown / stunCooldownDelay;

	//Cap the values
	if (temp < 0)
		temp = 0;
	else if (temp > 1)
		temp = 1;

	//Invert
	return 1 - temp;
}

void AMazeCharacter::SpeedBoost(float amount)
{
	moveSpeed += moveSpeed * amount;
}
