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

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if() actor is inside, then call
	if (PressurePlate->IsOverlappingActor(PlayerPawn))
	{
		OpenDoor();
	}

}

void UOpenDoor::OpenDoor() 
{
	AActor *gameObject = GetOwner();

	for (float i = 0.f; i < 90.f; i++)
	{
		FRotator NewRotation = FRotator(0.0f, i, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("The rotation now is: %s"), *NewRotation.ToString());
		gameObject->SetActorRotation(NewRotation);
	}
}