// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("MyMass"));
	SetRootComponent(MassWheelConstraint);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("MyWheel"));
	Wheel->SetupAttachment(MassWheelConstraint);

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MyMassWheelConstraint"));
	Mass->SetupAttachment(MassWheelConstraint);

	FConstrainComponentPropName A;
	FConstrainComponentPropName B;
	A.ComponentName = FName("MyMass");
	B.ComponentName = FName("MyWheel");
	MassWheelConstraint->ComponentName1 = A;
	MassWheelConstraint->ComponentName2 = B;


}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	if(GetAttachParentActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("helojecjcanffffffffffffaaaaaaaaaaaaaaaabbbbbbbbbbbbbb"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("helojecjcanfzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz"));
	}
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

