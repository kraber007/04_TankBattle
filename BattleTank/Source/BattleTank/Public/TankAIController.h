// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/World.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:

virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override ; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Closest AI tanks can get to player")
	float AcceptanceRadius = 8000;  // how close AI tank can get to player	
};
