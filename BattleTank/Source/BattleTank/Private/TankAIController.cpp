// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn()) ;
    auto ControlledTank = Cast<ATank>(GetPawn());
    
    if(!ensure(PlayerTank && ControlledTank)){return ;}
    ControlledTank->AimAt(PlayerTank->GetActorLocation(), ControlledTank->LaunchSpeed);
    ControlledTank->Fire(); 
    MoveToActor(PlayerTank, AcceptanceRadius); 

}


