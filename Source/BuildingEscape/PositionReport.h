/*
 BUILDING ESCAPE by Tomas Gonzalez-Ortega
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
#include "PositionReport.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UPositionReport : public UActorComponent
{ // class PositionReport which inherits from ActorComponent
	GENERATED_BODY()

public:
	UPositionReport(); // Sets default values for this component's properties

protected:
	virtual void BeginPlay() override; // Called when the game starts

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override; // Called every frame
};
