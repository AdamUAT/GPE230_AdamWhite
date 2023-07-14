// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Pickup.generated.h"

UENUM(BlueprintType)
enum EPickupType
{
	HEALTH UMETA(DisplayName = "Health"),
	SPEED UMETA(DisplayName = "Speed")
};

UCLASS()
class GPE230_ADAMWHITE_API APickup : public ATriggerBox
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditAnywhere)
		TEnumAsByte<EPickupType> pickupType;

	UFUNCTION()
		void CheckActorType(class AActor* OverlappedActor, AActor* OtherActor);

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnPickup(AActor* player);

};
