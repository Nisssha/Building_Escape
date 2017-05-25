// Fill out your copyright notice in the Description page of Project Settings.

#include "Section_02.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	gameObject = GetOwner();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if() actor is inside, then call
	if (GetTotalMassOfActorsOnPressurePlate() > TriggerMass) //should be a parameter, not a magic number
	{
		OnOpenRequest.Broadcast();
	}
	else
	{
		OnCloseRequest.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPressurePlate()
{
	float TotalMass = 0.f;
	TArray<AActor *> OverlappingActors;

	if (!PressurePlate) { return 0.f; }

	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for(auto &actor : OverlappingActors)
	{
		TotalMass += actor->GetRootPrimitiveComponent()->GetMass();
	}
	return TotalMass;
}