// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"
#include "BuildingEscape.h"
#include "Gameframework/Actor.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{   // Constructor
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
    FString ObjectName = GetOwner()->GetName();
    FVector ObjectPos = GetOwner()->GetActorLocation();
    //UE_LOG(LogTemp, Warning, TEXT("%s is at X=%f, Y=%f, Z=%f!"), *ObjectName, ObjectPos.X, ObjectPos.Y, ObjectPos.Z);
}

// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

