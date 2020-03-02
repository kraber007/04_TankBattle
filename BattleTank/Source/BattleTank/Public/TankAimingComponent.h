// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8 {Reloading, Aiming, Locked, NoAmmo};

class UTankBarrel; //forward declaration
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFUNCTION(BlueprintCallable, Category = Setup)
	void InitialiseBarrelTurret(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet) ;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 0.1;
	double LastFireTime = 0;
	
	

	EFiringStatus GetFiringStatus() const;

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	int32 GetTotalAmmo() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "FiringState")
	EFiringStatus FiringState = EFiringStatus::Reloading;

	UPROPERTY(BlueprintReadWrite, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;


public:
    UTankAimingComponent();
	UTankBarrel* Barrel = nullptr; 
	UTankTurret* Turret = nullptr;
	void MoveBarrelTowards() ;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 10000 ;

	FVector AimDirection;
	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = "TotalAmmo")
	int32 TotalAmmo = 10;
	
};
