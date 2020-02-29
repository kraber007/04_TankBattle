// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8 {Reloading, Aiming, Locked};

class UTankBarrel; //forward declaration
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFUNCTION(BlueprintCallable, Category = Setup)
	void InitialiseBarrelTurret(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet) ;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation, float LauchSpeed);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "FiringState")
	EFiringStatus FiringState = EFiringStatus::Reloading;

private:
    UTankAimingComponent();
	UTankBarrel* Barrel = nullptr; 
	UTankTurret* Turret = nullptr;
	void MoveBarrelTowards(FVector AimDirection) ;

};
