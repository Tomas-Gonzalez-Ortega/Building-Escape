// Tomas Gonzalez-Ortega

#include "Gameframework/Actor.h"
#include "DrawDebugHelpers.h"
#include "BuildingEscape.h"
#include "Grabber.h"
#define OUT

/// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::Grab()
{   // Line traces and checks for physics body collision with any other actor
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent(); // Gets the mesh
    auto ActorHit = HitResult.GetActor();
    if(ActorHit) // if we hit something
    {   // attach the Physics Handle
        if(!PhysicsHandle){return;}
        PhysicsHandle->GrabComponentAtLocation(
            ComponentToGrab, // ComponentToGrab
            NAME_None, // grab what bone name, if any; no bones needed
            ComponentToGrab->GetOwner()->GetActorLocation() // grab location
        );
    }
}

void UGrabber::Release()
{
    if(!PhysicsHandle){return;}
    PhysicsHandle->ReleaseComponent();
}

/// Called when the game starts
void UGrabber::BeginPlay()
{
    Super::BeginPlay();
    FindPhysicsHandleComponent();
    SetupInputComponent();
}

/// Looks for the attached Physics Handle through a generic
void UGrabber::FindPhysicsHandleComponent()
{
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if(PhysicsHandle == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing Physics Handle Component!"), *GetOwner()->GetName());
    }
}

/// Looks for the run time attached Input Components
void UGrabber::SetupInputComponent()
{
    InputComponent = GetOwner()->InputComponent;
    if(InputComponent)
    {// Binds the Input Axis using Grab into the address where the function is stored
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
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
    if(!PhysicsHandle){return;}
    if(PhysicsHandle->GrabbedComponent) // if the Physics Handle is attached
    {
        PhysicsHandle->SetTargetLocation(GetReachLineEnd());
    }
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{   /// Ray-casts out to reach distance
    FHitResult HitResult;
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    GetWorld()->LineTraceSingleByObjectType(
        OUT HitResult,
        GetReachLineStart(),
        GetReachLineEnd(),
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParameters
    );
    return HitResult;
}

FVector UGrabber::GetReachLineStart()
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
    );
    return PlayerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd()
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
    );
    return PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
}
