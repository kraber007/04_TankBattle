// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringState;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = 	FPlatformTime::Seconds();

}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(LogTemp, Warning, TEXT("I am tiiiiiiiiiiickiiiiiiing"));
	if(TotalAmmo <=0)
	{
		FiringState = EFiringStatus::NoAmmo;
	}
	else if( (FPlatformTime::Seconds() - LastFireTime < ReloadTimeInSeconds) )
	{
		FiringState = EFiringStatus::Reloading;
	}
	else if(IsBarrelMoving())
	{
		FiringState = EFiringStatus::Aiming;
	}
	else
	{
		FiringState = EFiringStatus::Locked;
	}
	
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if(!ensure(Barrel)){return 0;}
	return !(Barrel->GetForwardVector().Equals(AimDirection, 0.01));
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if(!ensure(Barrel)){return ;}
	auto BarrelLocation = Barrel->GetComponentLocation();
	
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
		AimDirection = OutTossVelocity.GetSafeNormal();
		MoveBarrelTowards();
	}
}


void UTankAimingComponent::InitialiseBarrelTurret(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards()
{
	if(!ensure(Barrel && Turret)){return ;}
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("Aiming rotator is %s"), *AimAsRotator.ToString());
	auto DeltaRotatorBarrel = AimAsRotator - BarrelRotator;		   //I think these two will be same
	auto DeltaRotatorTurret = AimAsRotator - TurretRotator;        //I think these two will be same

	Barrel->Elevate(DeltaRotatorBarrel.Pitch);  //TODO remove magic number
	if(FMath::Abs(DeltaRotatorTurret.Yaw) <=180)
	{
	Turret->RotateTurret(DeltaRotatorTurret.Yaw);
	}
	else // avoid going the long way
	{
		Turret->RotateTurret(-DeltaRotatorTurret.Yaw);
	}
	
}

void UTankAimingComponent::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("Firing %s"), *GetOwner()->GetName());
	if(!ensure(Barrel)){return ;}
	if(!ensure(ProjectileBlueprint)){return ;}
	if((FiringState != EFiringStatus::Reloading)  && (TotalAmmo > 0) )
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")),Barrel->GetSocketRotation(FName("Projectile")));
		if(!ensure(Projectile)){return ;}
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		--TotalAmmo;
	}
	
}

int32 UTankAimingComponent::GetTotalAmmo() const
{
	return TotalAmmo;
}