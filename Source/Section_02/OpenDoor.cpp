// Fill out your copyright notice in the Description page of Project Settings.

#include "Section_02.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
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
