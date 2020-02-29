// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta=(BlueprintSpawnableComponent) , hidecategories = "Collision")
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);  // +1 is 20 and -1 is -20

private:

	UPROPERTY(EditDefaultsOnly, Category = TankBarrel_Setup)
	float MaxDegreesPerSecond = 10;  //assuming default

	UPROPERTY(EditDefaultsOnly, Category = TankBarrel_Setup)
	float MaxElevationDegrees = 40;

	UPROPERTY(EditDefaultsOnly, Category = TankBarrel_Setup)
	float MinElevationDegrees = 0;
};
