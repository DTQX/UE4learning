// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel || !Turret) {
		return;
	}

	FVector OutLanuchVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLanuchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		))
	{
		FVector AimDirection = OutLanuchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		auto OurTankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Proj found"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Proj not found"));
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet) {
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());
	
	Barrel->Elevate(DeltaRotator.Pitch); 
	Turret->Rotate(DeltaRotator.Yaw);
}

//void UTankAimingComponent::MoveTurret(FVector AimDirection) {
//	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
//	FRotator AimAsRotator = AimDirection.Rotation();
//	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
//	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());
//
//	Barrel->Elevate(DeltaRotator.Pitch); //TODO remove magic
//
//}
