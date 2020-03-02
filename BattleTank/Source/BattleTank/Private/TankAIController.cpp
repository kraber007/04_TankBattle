// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"          //  need to register OnDeath we tried at avoid including tank but here we are.... blah blah blah....
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
    if(!(GetWorld()->GetFirstPlayerController())){return;}
    ControlledTankAimingComponent->AimAt(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
    MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(), AcceptanceRadius);
    if(ControlledTankAimingComponent->GetFiringStatus() == EFiringStatus::Locked)
    ControlledTankAimingComponent->Fire();
    
}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if(!(InPawn)){return;}
    auto PossessedTank = Cast<ATank>(InPawn);
    if(!ensure(PossessedTank)){return;}
    PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
}

void ATankAIController::OnPossessedTankDeath()
{
    GetPawn()->DetachFromControllerPendingDestroy();
}


