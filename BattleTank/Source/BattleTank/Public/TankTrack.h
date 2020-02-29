// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
  Tank Track is used to haul the tank around this horrible world
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable , Category = Input)
	void SetThrottle(float Throttle);

	UPROPERTY(EditDefaultsOnly, Category = Drive)  //in newtons
	float TrackMaxDrivingForce = 400000;
};
