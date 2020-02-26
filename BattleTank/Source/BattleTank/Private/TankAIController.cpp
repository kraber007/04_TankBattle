// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    ATank* PossessedTank = GetControlledTank();
    if(!PossessedTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Controlled Tank not found"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("%s has possessed %s"), *GetName(), *PossessedTank->GetName());
    }
    
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}