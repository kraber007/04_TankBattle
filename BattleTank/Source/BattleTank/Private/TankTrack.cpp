// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
    //UE_LOG(LogTemp, Warning, TEXT("%f: %s throttling at %f"), GetWorld()->GetTimeSeconds(), *GetName(), Throttle);
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce ;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    if(!ensure(TankRoot)){return ;}
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}