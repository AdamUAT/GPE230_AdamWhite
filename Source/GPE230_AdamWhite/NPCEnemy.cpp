// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCEnemy.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Health.h"

// Sets default values
ANPCEnemy::ANPCEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPCEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANPCEnemy::DetectHit()
{
	//Killswitch for damaging the player.
	bool canDamage = true;

	//Get the location of the fist
	const FVector PunchLocation = GetMesh()->GetSocketLocation(_PunchingHandSocketName);

	//Set up the ignored actors
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	ActorsToIgnore.Add(GetOwner());
	
	//Actors overlaped by the sphere.
	TArray<FHitResult> HitArray;

	//Spheretrace
	const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), PunchLocation, PunchLocation, _TraceRadius,
		UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorsToIgnore, EDrawDebugTrace::None, HitArray,
		true, FLinearColor::Red, FLinearColor::Green, 2.0f);

	//Debug code
	FString ownerName = this->GetName();

	if (Hit)
	{
		for (const FHitResult HitResult : HitArray)
		{
			if (canDamage)
			{
				//Get the health component. This only damages actors with health components.
				TArray<UHealth*> healthComps;
				HitResult.GetActor()->GetComponents(healthComps);

				//Make sure there was at least 1 health component
				if (healthComps.Num() > 0)
				{
					//Assign the first health component to a variable.
					UHealth* healthComp = healthComps[0];

					//Apply damage
					healthComp->TakeDamage(_HitDamage);

					//Print debug text
					UE_LOG(LogTemp, Log, TEXT("NPCEnemy actor \"%s\" hit other actor \"%s\", dealing %f damage."), *ownerName, *(HitResult.GetActor()->GetName()), _HitDamage);

					canDamage = false;
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("NPCEnemy actor \"%s\" did not detect any valid hits on its last attack."), *ownerName);
	}
}

// Called to bind functionality to input
void ANPCEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

