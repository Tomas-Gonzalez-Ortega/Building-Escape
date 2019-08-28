// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionReport.h"
#include "BuildingEscape.h"
#include "Gameframework/Actor.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them. Constructor
    bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
    FString ObjectName = GetOwner()->GetName();
    FVector ObjectPos = GetOwner()->GetActorLocation();
    UE_LOG(LogTemp, Warning, TEXT("%s is at X=%f, Y=%f, Z=%f!"), *ObjectName, ObjectPos.X, ObjectPos.Y, ObjectPos.Z);
    /* GetOwner access the Actor through a pointer then GetTransform access the Vector information of this Actor, then the position and finally its parsed into a String
     FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();
     // Calls a MACRO, FYI *ObjectName is an overload method, not an actual de-reference
     UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *ObjectName, *ObjectPos);
     */
}

// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

