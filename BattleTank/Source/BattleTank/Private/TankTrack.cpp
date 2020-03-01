// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    UE_LOG(LogTemp, Warning, TEXT("Track ticking"));

    auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector()) ; //slipping in right direction
    auto CorrectionAcceleration = (-1)*(SlippageSpeed/DeltaTime)*(GetRightVector());
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = 1*(TankRoot->GetMass() * CorrectionAcceleration)/2 ;  // 2 because two 2 tracks on a tank
    TankRoot->AddForce(CorrectionForce);
}    

void UTankTrack::SetThrottle(float Throttle)
{
    //UE_LOG(LogTemp, Warning, TEXT("%f: %s throttling at %f"), GetWorld()->GetTimeSeconds(), *GetName(), Throttle);
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce ;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    if(!ensure(TankRoot)){return ;}
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}