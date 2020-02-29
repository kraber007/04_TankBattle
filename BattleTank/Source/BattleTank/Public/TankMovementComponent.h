// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * Responsible for wire flying
 */
UCLASS(ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
protected:
	
public:
	UFUNCTION(BlueprintCallable)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable)
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = Setupsi)
	void Initialise(UTankTrack* LeftTrack, UTankTrack* RightTrack);

private:
	virtual void RequestDirectMove(const FVector & MoveVelocity,bool bForceMaxSpeed) override;
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	
};
