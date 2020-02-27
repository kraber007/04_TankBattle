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

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("%s is Ticking"), *GetName());
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const 
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetControlledTank()) {return; }
    FVector HitLocation;               // Out Parameter
    GetSightRayHitLocation(HitLocation);
    UE_LOG(LogTemp, Warning, TEXT("AimDirection: %s"), *HitLocation.ToString());

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    int32 ViewportSizeX, ViewportSizeY ;         //Out Parameters
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairLocationX, ViewportSizeY*CrossHairLocationY) ;

    //Getting unitvector along lookDirection
    FVector CameraWorldLocation, WorldDirection ;   // To be discarded and Out parameter
    DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, WorldDirection) ;
    HitLocation = WorldDirection ; // temperory##################################################################################################################

    return true;
}


