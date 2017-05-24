// Fill out your copyright notice in the Description page of Project Settings.

#include "Section_02.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FString objectName = GetOwner()->GetName();
	FString objectPositionString = GetOwner()->GetActorLocation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("I'm still %s, but now let's see my location with string: %s"), *objectName, *objectPositionString);
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FVector pos;
	FRotator rot;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT pos, OUT rot);
	/*
	UE_LOG(LogTemp, Warning, TEXT("%s, %s"), *pos.ToString(), *rot.ToString());
	*/

	///Query parameters
	FCollisionQueryParams QueryParams (FName(TEXT("")), false, GetOwner());

	FVector LineTraceEnd = pos + (rot.Vector()*Reach);

	DrawDebugLine(GetWorld(), pos, LineTraceEnd,  FColor (255,0,0), false, 0.f, 0.f, 10.f);

	FHitResult LineTraceHit;

	GetWorld()->LineTraceSingleByObjectType(OUT LineTraceHit, pos, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), QueryParams);

	AActor* ActorHit = LineTraceHit.GetActor();

	if (ActorHit) 
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(ActorHit->GetName()));
	}
}

