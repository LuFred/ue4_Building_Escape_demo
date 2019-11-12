// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoorComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenDoorRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseDoorRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float NewDoorRotator=-60.f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;
	void OpenDoor();
	void CloseDoor();

	UPROPERTY(BlueprintAssignable)
	FOnOpenDoorRequest OnOpenDoorRequest;
	UPROPERTY(BlueprintAssignable)
	FOnCloseDoorRequest OnCloseDoorRequest;
};
