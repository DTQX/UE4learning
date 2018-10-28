// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANK_BATTLE_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnyWhere)
		float MaxDegreesPerSecond = 10.0;

	UPROPERTY(EditAnyWhere)
		float MaxElevationDegrees = 40;

	UPROPERTY(EditAnyWhere)
		float MinElevationDegrees = 0;
};
