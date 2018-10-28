// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	if (LeftTrackToSet && RightTrackToSet)
	{
		LeftTrack = LeftTrackToSet;
		RightTrack = RightTrackToSet;
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	UE_LOG(LogTemp, Warning, TEXT("MoveVelocity: %s, time %f"), *MoveVelocity.ToString(), GetWorld()->GetTimeSeconds());

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	UE_LOG(LogTemp, Warning, TEXT("GetActorForwardVector: %s, time %f"), *TankForward.ToString());
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	auto LeftThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendRotate(LeftThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (LeftTrack && RightTrack) {
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	}
	
}

void UTankMovementComponent::IntendRotate(float Throw) {
	if (LeftTrack && RightTrack) {
		Throw *= 1.5;
		LeftTrack->SetThrottle(-Throw);
		RightTrack->SetThrottle(Throw);
	}
}