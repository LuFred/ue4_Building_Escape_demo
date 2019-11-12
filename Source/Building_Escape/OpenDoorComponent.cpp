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
	AActor* actor=	GetWorld()->GetFirstPlayerController()->GetPawn();
	//	UE_LOG(LogTemp,Warning,TEXT("Open door %s"),*actor->GetName());
	if(actor->IsOverlappingActor(PressurePlate))
	{
		UE_LOG(LogTemp,Warning,TEXT("Open door ---xx"));
		OpenDoor();
	}else
	{
		CloseDoor();
	}
	
	
	// ...
}

void UOpenDoorComponent::OpenDoor()
{
	
	UE_LOG(LogTemp,Warning,TEXT("Open door ---"));
	OnOpenDoorRequest.Broadcast();
	// FRotator NewRotator(0.f,NewDoorRotator,0.f);
	// GetOwner()->SetActorRotation(NewRotator);
}
void UOpenDoorComponent::CloseDoor()
{
	UE_LOG(LogTemp,Warning,TEXT("Close door ----"));
	OnCloseDoorRequest.Broadcast();
}
