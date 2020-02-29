// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/World.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:

virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override ; 
	
private:
	float AcceptanceRadius = 3000;  // how close AI tank can get to player	
};
