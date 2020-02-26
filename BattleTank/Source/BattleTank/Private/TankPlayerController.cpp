// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Helo there from TankPlayerController"));

    ATank* MyTank = GetControlledTank();
    if(!MyTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Tank not found"));
    }
    else
    {
        UE_LOG(LogTemp,Warning, TEXT("Player is controlling %s"),*MyTank->GetName()); 
    }
    

}

ATank* ATankPlayerController::GetControlledTank() const 
{
    return Cast<ATank>(GetPawn());
}

