// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class TANK_BATTLE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATank* GetPlayerTank() const;

	ATank* GetControlledTank() const;

	void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:
	//How close can the AI tank get
	float AcceptanceRadius = 0;
};
