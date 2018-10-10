// Fill out your copyright notice in the Description page of Project Settings.

#include "Graber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/ActorComponent.h"
#include "DrawDebugHelpers.h"

#define OUT


// Sets default values for this component's properties
UGraber::UGraber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGraber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp, Warning, TEXT("graber init complete!"));
	physicHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("find PhysicHandle"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not find PhysicHandle"));
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("found InputComponent"));

		InputComponent->BindAction("Grab", IE_Pressed, this, &UGraber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGraber::Releas);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not find InputComponent"));
	}
}


// Called every frame
void UGraber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	/*UE_LOG(LogTemp, Warning, TEXT("Location %s, Rotation %s"),
		*PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());*/
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Length;


	if (physicHandle->GetGrabbedComponent())
	{
		physicHandle->SetTargetLocation(LineTraceEnd);
	}
}

void UGraber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed!"));

	auto HitResult =  GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		physicHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true
		);
	}
	
}

void UGraber::Releas()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab release!"));
	physicHandle->ReleaseComponent();
}

const FHitResult UGraber::GetFirstPhysicsBodyInReach()
{
	///get
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	/*UE_LOG(LogTemp, Warning, TEXT("Location %s, Rotation %s"),
		*PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());*/
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Length;
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0,
		10.f
	);

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor* HitObject = Hit.GetActor();
	if (HitObject) {
		UE_LOG(LogTemp, Warning, TEXT("HitObject Name: %s"), *HitObject->GetName());
	}
	return Hit;
}


