/*
 BUILDING SCAPE by Tomas Gonzalez-Ortega
 Vancouver, BC, September 2019
 Demo based on Udemy - https://www.udemy.com/unrealcourse
 Unreal Engine C++ Developer: Learn C++ and Make Video Games by Ben Tristem
 Japanese Shrine Mini asset pack by Bandinanquest
 Original Soundtrack by Tomas-Gonzalez using Pro Tools 2018.12
 Door Audio sampled by Tomas-Gonzalez
*/

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	UGrabber(); // Sets default values for this component's properties
	virtual void BeginPlay() override; // Called when the game starts
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override; // Called every frame

private:
    float Reach = 100.f; // How far ahead of the player can we reach in cm
    UPhysicsHandleComponent* PhysicsHandle = nullptr;
    UInputComponent* InputComponent = nullptr;
    void Grab();
    void Release();
    void FindPhysicsHandleComponent();
    void SetupInputComponent();
    const FHitResult GetFirstPhysicsBodyInReach(); // const maybe at the end of the line
    FVector GetReachLineStart();
    FVector GetReachLineEnd();
};
