// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

    if(!ensure(AimingComponent)){return ;}
    FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("%s is Ticking"), *GetName());
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetPawn()){return;}
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent)) {return; }
    FVector HitLocation;               // Out Parameter
    GetSightRayHitLocation(HitLocation);
    AimingComponent->AimAt(HitLocation);

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    int32 ViewportSizeX, ViewportSizeY ;         //Out Parameters
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairLocationX, ViewportSizeY*CrossHairLocationY) ;

    //Getting unitvector along lookDirection
    FVector CameraWorldLocation, WorldDirection ;   // To be discarded and Out parameter
    DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, WorldDirection) ;

    if( GetLookVectorHitLocation(WorldDirection, HitLocation))
    {
        return true;
    }
    else {return false;}    
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation = StartLocation + (LookDirection * LineTraceRange) ;
    FHitResult HitResult ;
    if( GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera) )
    {
        HitLocation = HitResult.Location ;
        return true;
    }
    else
    {
        HitLocation = FVector(0,0,0);
        return false;
    }
}

void ATankPlayerController::OnPossessedTankDeath()
{
    UE_LOG(LogTemp, Warning, TEXT(" problem in calling StartSpectatingOnly() I am not feeling so good..................."));
    StartSpectatingOnly();
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if(!(InPawn)){return;}
    auto PossessedTank = Cast<ATank>(InPawn);
    if(!ensure(PossessedTank)){return;}
    PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
}

