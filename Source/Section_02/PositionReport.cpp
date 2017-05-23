// Fill out your copyright notice in the Description page of Project Settings.

#include "Section_02.h"
#include "PositionReport.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	FString objectName = GetOwner()->GetName();
	//FVector objectPosition = GetOwner()->GetActorLocation();
	FString objectPositionString = GetOwner()->GetActorLocation().ToString();

	//UE_LOG(LogTemp, Warning, TEXT("Mornin' report! I'm the %s, standing at: x: %d, y: %d, z: %d."), *objectName, objectPosition[0], objectPosition[1], objectPosition[2]);
	UE_LOG(LogTemp, Warning, TEXT("I'm still %s, but now let's see my location with string: %s"), *objectName, *objectPositionString);
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

