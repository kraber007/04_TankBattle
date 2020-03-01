// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //auto Player = Cast<ATank>() ;
    auto ControlledTankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    
    if(!ensure(ControlledTankAimingComponent)){return ;}
    ControlledTankAimingComponent->AimAt(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
    ControlledTankAimingComponent->Fire();
    MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(), AcceptanceRadius);
    
    
    

}


