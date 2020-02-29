// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
    UE_LOG(LogTemp, Warning, TEXT("%f: %s throttling at %f"), GetWorld()->GetTimeSeconds(), *GetName(), Throttle);
}