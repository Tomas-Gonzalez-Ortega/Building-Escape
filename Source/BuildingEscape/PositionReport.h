// Fill out your copyright notice in the Description page of Project Settings.

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
