// Tomas Gonzalez-Ortega


#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UOpenDoor::BeginPlay()
{
    Super::BeginPlay();
    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
    AActor* Owner = GetOwner(); // Finds the owning Actor
    FRotator NewRotation = FRotator(0.0f, 60.0f, 0.0f); // This rotates the door in 60°
    Owner->SetActorRotation(NewRotation); // Sets the door rotation
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Poll the Trigger Volume and if the Actor is in the volume open the door
    if(PressurePlate->IsOverlappingActor(ActorThatOpens)){
        OpenDoor();
    }
}

