// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    ATank* PossessedTank = GetControlledTank();
    auto PlayerTank = GetPlayerTank();
    if(!PossessedTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Controlled Tank not found"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("%s has possessed %s"), *GetName(), *PossessedTank->GetName());
    }
    if(!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI tank can't find player tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("%s has found %s"), *GetName(), *PlayerTank->GetName());
    }
    
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn()) ;
}