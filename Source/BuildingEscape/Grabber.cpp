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
    // bWantsBeginPlay = true; DEPRECATED
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::Grab(){
    UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
}

void UGrabber::Release(){
    UE_LOG(LogTemp, Warning, TEXT("Grab released"));
}

/// Called when the game starts
void UGrabber::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
    
    /// Looks for the attached Physics Handle through a generic
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if(PhysicsHandle)
    {
        UE_LOG(LogTemp, Warning, TEXT("Physics Handle found"));
    }
    else
    {
         UE_LOG(LogTemp, Error, TEXT("%s missing Physics Handle Component!"), *GetOwner()->GetName());
    }
    
    /// Looks for the run time attached Input Components
    InputComponent = GetOwner()->InputComponent;
    if(InputComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("Input Components found!"));
        // Binds the Input Axis using Grab into the address where the function is stored
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        // Checks if the Grab Action is being released and calls Release
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing Input Components!"), *GetOwner()->GetName());
    }
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

