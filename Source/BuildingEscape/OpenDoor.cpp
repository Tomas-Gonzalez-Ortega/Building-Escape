/*
 BUILDING SCAPE by Tomas Gonzalez-Ortega
 Vancouver, BC, September 2019
 Demo based on Udemy - https://www.udemy.com/unrealcourse
 Unreal Engine C++ Developer: Learn C++ and Make Video Games by Ben Tristem
 Japanese Shrine Mini asset pack by Bandinanquest
 Original Soundtrack by Tomas-Gonzalez using Pro Tools 2018.12
 Door Audio sampled by Tomas-Gonzalez
*/

#include "OpenDoor.h"
#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::BeginPlay()
{
    Super::BeginPlay();
    Owner = GetOwner();
    if(!PressurePlate)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName());
    }
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Polls the Trigger Volume
    if(GetTotalMassOfActorsOnPlate() > TriggerMass)
    {
        OnOpen.Broadcast();
    }
    else
    {
        OnClose.Broadcast();
    }
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
    float TotalMass = 0.f;
    TArray<AActor*> OverlappingActors;
    // Finds the overlapping actors
    if(!PressurePlate){return TotalMass;}
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);
    // Iterates through them and adds their masses
    for (const auto* Actor : OverlappingActors)
    {
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }
    return TotalMass;
}
