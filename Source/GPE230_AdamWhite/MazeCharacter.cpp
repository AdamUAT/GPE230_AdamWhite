// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Stunnable.h"


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

// Called to bind functionality to input
void AMazeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &AMazeCharacter::MoveFB);
	PlayerInputComponent->BindAxis(TEXT("MoveLR"), this, &AMazeCharacter::MoveLR);
	PlayerInputComponent->BindAxis(TEXT("Rotate"), this, &AMazeCharacter::Rotate);
	PlayerInputComponent->BindAction("Stun", IE_Pressed, this, &AMazeCharacter::Stun);
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

void AMazeCharacter::SpeedBoost(float amount)
{
	moveSpeed += moveSpeed * amount;
}
