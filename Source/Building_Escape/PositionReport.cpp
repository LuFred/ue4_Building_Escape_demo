// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionReport.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("position report reporting for duty!"));
	// ...
	
	AActor* owner=GetOwner();
	FString AName=owner->GetName();
	FRotator ARota=owner->GetActorRotation();
	FRotator NewRotation=FRotator(0.0f,-70.0f,0.0f);
	owner->SetActorRotation(NewRotation);
	UE_LOG(LogTemp,Warning,TEXT("actor name=%s current rotation is %s move to %s"),*AName,*ARota.ToString(),*NewRotation.ToString());
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(LogTemp,Warning,TEXT("tick position !"));
	// ...
}

