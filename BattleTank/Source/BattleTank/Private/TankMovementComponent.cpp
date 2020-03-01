// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if(!ensure(LeftTrack && RightTrack)){return;}
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    if(!ensure(LeftTrack && RightTrack)){return;}
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
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto MoveVelocityIntention = MoveVelocity.GetSafeNormal();

    auto CosTheta = FVector::DotProduct(TankForward,MoveVelocityIntention);
    IntendMoveForward(CosTheta);

    auto SineTheta = FVector::CrossProduct(MoveVelocityIntention, TankForward) ;
    auto xxx = (SineTheta.Size())*(FMath::Sign(SineTheta.Z))*(-1);
    IntendTurnRight(xxx);
    ////UE_LOG(LogTemp, Warning, TEXT("%f: moving with: %f"), GetWorld()->GetTimeSeconds(), CosTheta);
    ////UE_LOG(LogTemp, Warning, TEXT("%f: cross AAAAAAAAAAAAAA with: %f"), GetWorld()->GetTimeSeconds(), xxx);
}

