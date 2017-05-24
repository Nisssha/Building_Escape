// Fill out your copyright notice in the Description page of Project Settings.

#include "Section_02.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	gameObject = GetOwner();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if() actor is inside, then call
	if (PressurePlate->IsOverlappingActor(PlayerPawn))
	{
		OpenDoor();
		LastTimeDoorOpened = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastTimeDoorOpened > DoorCloseDelay)
	{
		CloseDoor();
	}
}

void UOpenDoor::OpenDoor() 
{
		FRotator NewRotation = FRotator(0.0f, 90.0f, 0.0f);
		gameObject->SetActorRotation(NewRotation);
}

void UOpenDoor::CloseDoor()
{
		FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);
		gameObject->SetActorRotation(NewRotation);
}
