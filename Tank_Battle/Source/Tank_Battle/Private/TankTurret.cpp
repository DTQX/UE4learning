// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	auto Time = GetWorld()->GetTimeSeconds();
	float ABSRelativeSpeed = FMath::Abs(RelativeSpeed);
	if (360 - ABSRelativeSpeed < ABSRelativeSpeed)
	{
		RelativeSpeed = 0 - RelativeSpeed;
	}

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	//auto Rotation = FMath::Clamp<float>(RawNewRotation, MinRotationDegrees, MaxRotationDegrees);
	SetRelativeRotation(FRotator(0, Rotation, 0));

	UE_LOG(LogTemp, Warning, TEXT("Time: %f"), Time);
}