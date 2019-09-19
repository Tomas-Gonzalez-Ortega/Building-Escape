/*
 BUILDING ESCAPE by Tomas Gonzalez-Ortega
 Vancouver, BC, September 2019
 Demo based on Udemy - https://www.udemy.com/unrealcourse
 Unreal Engine C++ Developer: Learn C++ and Make Video Games by Ben Tristem
 Japanese Shrine Mini asset pack by Bandinanquest
 Original Soundtrack by Tomas-Gonzalez using Pro Tools 2018.12
 Door Audio sampled by Tomas-Gonzalez
*/

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

