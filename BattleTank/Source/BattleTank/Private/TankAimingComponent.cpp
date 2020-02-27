// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	auto BarrelLocation = Barrel->GetComponentLocation();
	UE_LOG(LogTemp, Warning, TEXT("%s Aiming at: %s from %s  and Will fire at will at %f"),*GetOwner()->GetName(), *HitLocation.ToString(), *BarrelLocation.ToString(), LaunchSpeed);
	if(!Barrel){return ;}
	
	FVector OutTossVelocity{0};
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if(	UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutTossVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		)
	)
	{
		auto AimDirection = OutTossVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Aiming Direction is %s"), *AimDirection.ToString());
	}

	else{return;}

}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}