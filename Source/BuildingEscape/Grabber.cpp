// Tomas Gonzalez-Ortega

#include "Gameframework/Actor.h"
#include "DrawDebugHelpers.h"
#include "BuildingEscape.h"
#include "Grabber.h"
#define OUT

/// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


/// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
}


/// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
	// Gets player viewpoint this tick
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
    );
    
    /// Logs out every tick
    UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewPointLocation.ToString(),
        *PlayerViewPointRotation.ToString()
    )
    
    FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
    /// Traces a red line to visualize the players reach with the grabber
    DrawDebugLine(
        GetWorld(),
        PlayerViewPointLocation,
        LineTraceEnd,
        FColor(255, 0, 0),
        false,
        0.f,
        0.f,
        10.f
    );
    
    /// Setup query Parameters
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    
    /// Ray-casts out to reach distance
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(
        OUT Hit,
        PlayerViewPointLocation,
        LineTraceEnd,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParameters
    );
    
    /// See what it hits
    AActor* ActorHit = Hit.GetActor();
    if(ActorHit)
    {
        UE_LOG(LogTemp, Warning, TEXT("Line trace hits: %s"), *(ActorHit->GetName()))
    }
}

