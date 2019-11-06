// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CollisionQueryParams.h"
#include "GrabberComponent.h"

#define OUT 
// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("Event Function:BeginPlay"));
	FindInputHandleComponent();
	FindPhysicsHandleComponent();
	// ...
	
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	DebugLine();

	FVector PlayerLocation;
	FRotator PlayerRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerLocation,
		OUT PlayerRotator
	);
	FVector LineTraceEnd=PlayerLocation+PlayerRotator.Vector()*Reach;
	if (PhysicsHandle!=nullptr){
	if(PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
	}


}

void UGrabberComponent::Grab(){
	UE_LOG(LogTemp,Warning,TEXT("InputComponent Event Function:Grab"));
	auto HitResult=GetFirstPhysicsBodyInReach();
	auto ComponentToGrab=HitResult.GetComponent();
	auto ActorHit=HitResult.GetActor();
	if(ActorHit)
	{
		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation()
		);
	}
}

void UGrabberComponent::Release(){
	UE_LOG(LogTemp,Warning,TEXT("InputComponent Event Function:Release"));
	PhysicsHandle->ReleaseComponent();
}
void UGrabberComponent::FindInputHandleComponent()
{
	InputComponent=GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputComponent){
		///UE_LOG(LogTemp,Warning,TEXT("%s InputComponent is found %s"),*(GetOwner()->GetName()),*InputComponent->GetName());
		InputComponent->BindAction("Grab",IE_Pressed,this,&UGrabberComponent::Grab);
		InputComponent->BindAction("Grab",IE_Released,this,&UGrabberComponent::Release);
	}else
	{
		UE_LOG(LogTemp,Warning,TEXT("InputComponent is not found"));
	}
	
}
void UGrabberComponent::FindPhysicsHandleComponent()
{
	PhysicsHandle=GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle){
		UE_LOG(LogTemp,Warning,TEXT("PhysicsHandle1 is  found"));
	}else
	{
		UE_LOG(LogTemp,Warning,TEXT("PhysicsHandle2 is not found"));
	}
}

void UGrabberComponent::DebugLine()
{
	FVector PlayerLocation;
	FRotator PlayerRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerLocation,
		OUT PlayerRotator
	);
	DrawDebugLine(
		GetWorld(),
		PlayerLocation,
		PlayerLocation+PlayerRotator.Vector()*30,
		FColor(255,0,0),
		false,
		0,
		0,
		3.f
	);
}
const FHitResult UGrabberComponent::GetFirstPhysicsBodyInReach()
{
	FVector PlayerLocation;
	FRotator PlayerRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerLocation,
		OUT PlayerRotator
	);
	FVector LineTraceEnd=PlayerLocation+PlayerRotator.Vector()*Reach;
	FCollisionQueryParams TraceParameters(FName(TEXT("")),false,GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	AActor* ActorHit=Hit.GetActor();
	if(ActorHit){
		UE_LOG(LogTemp,Warning,TEXT("Line Trace Hit:%s "),*(ActorHit->GetName()));
	}else{
		UE_LOG(LogTemp,Warning,TEXT("Line Trace Hit:not found "));
	}
	return Hit;
}