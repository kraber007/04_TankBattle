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

    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();
    
    if(!(PlayerTank && ControlledTank)){return;}
    
    MoveToActor(PlayerTank, AcceptanceRadius);

    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    if(AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
    {
        AimingComponent->Fire();
    }    
    
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


