// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "OpenDoorComponent.h"

// Sets default values for this component's properties
UOpenDoorComponent::UOpenDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UOpenDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AActor* actor=GetOwner();
	if(actor->IsOverlappingActor(PressurePlate))
	{
		OpenDoor();
	}else
	{
		CloseDoor();
	}
	
	UE_LOG(LogTemp,Warning,TEXT("Open door actor %s"),*actor->GetName());
	// ...
}

void UOpenDoorComponent::OpenDoor()
{
	FRotator NewRotator(0.f,NewDoorRotator,0.f);
	GetOwner()->SetActorRotation(NewRotator);
}
void UOpenDoorComponent::CloseDoor()
{
	FRotator NewRotator(0.f,0.f,0.f);
	GetOwner()->SetActorRotation(NewRotator);
}
