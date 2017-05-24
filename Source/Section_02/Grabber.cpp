// Fill out your copyright notice in the Description page of Project Settings.

#include "Section_02.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UGrabber::Grab()
{
	auto FirstHit = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = FirstHit.GetComponent();
	auto ActorHit = FirstHit.GetActor();

	if (ActorHit != nullptr)
	{
		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}
}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsComponent();
	FindInputComponent();
}

void UGrabber::FindPhysicsComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle){}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The physics handle is missing on %s object"), *GetOwner()->GetName());
	}
}

void UGrabber::FindInputComponent()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();

	if (Input)
	{
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The input component is missing on %s object"), *GetOwner()->GetName());
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	

	FHitResult ObjectPosition = GetFirstPhysicsBodyInReach();

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(ObjectPosition.TraceEnd);
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector pos;
	FRotator rot;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT pos, OUT rot);

	///Query parameters
	FCollisionQueryParams QueryParams(FName(TEXT("")), false, GetOwner());

	FVector LineTraceEnd = pos + (rot.Vector()*Reach);

	FHitResult LineTraceHit;

	GetWorld()->LineTraceSingleByObjectType(OUT LineTraceHit, pos, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), QueryParams);

	return LineTraceHit;
}