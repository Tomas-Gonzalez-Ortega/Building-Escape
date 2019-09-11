// Tomas Gonzalez-Ortega

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent); // This is a whole new class
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	UOpenDoor(); // Sets default values for this component's properties
    virtual void BeginPlay() override; // Called when the game starts
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override; // Called every frame
    UPROPERTY(BlueprintAssignable)
    FDoorEvent OnOpen;
    UPROPERTY(BlueprintAssignable)
    FDoorEvent OnClose;

private:
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate = nullptr;
    UPROPERTY(EditAnywhere)
    float TriggerMass = 30.f;
    AActor* Owner = nullptr; // The owning Door
    float GetTotalMassOfActorsOnPlate(); // returns total mass in Kilograms
};
