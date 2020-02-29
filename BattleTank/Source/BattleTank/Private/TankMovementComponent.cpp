// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    //UE_LOG(LogTemp, Warning, TEXT("throw: %f"), Throw);
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    //UE_LOG(LogTemp, Warning, TEXT("throw: %f"), Throw);
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
    
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity,bool bForceMaxSpeed)
{
    auto  TankName = GetOwner()->GetName();
    UE_LOG(LogTemp, Warning, TEXT("%s moving with %s"), *TankName, *MoveVelocity.ToString());
}
