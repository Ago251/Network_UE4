// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterGame.h"
#include "Player/ShooterCharacterMovement.h"

//----------------------------------------------------------------------//
// UPawnMovementComponent
//----------------------------------------------------------------------//
UShooterCharacterMovement::UShooterCharacterMovement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


float UShooterCharacterMovement::GetMaxSpeed() const
{
	float MaxSpeed = Super::GetMaxSpeed();

	const AShooterCharacter* ShooterCharacterOwner = Cast<AShooterCharacter>(PawnOwner);
	if (ShooterCharacterOwner)
	{
		if (ShooterCharacterOwner->IsTargeting())
		{
			MaxSpeed *= ShooterCharacterOwner->GetTargetingSpeedModifier();
		}
		if (ShooterCharacterOwner->IsRunning())
		{
			MaxSpeed *= ShooterCharacterOwner->GetRunningSpeedModifier();
		}
	}

	return MaxSpeed;
}

void UShooterCharacterMovement::PhysCustom(float deltaTime, int32 Iterations) {
	const AShooterCharacter* ShooterCharacterOwner = Cast<AShooterCharacter>(PawnOwner);
	switch (CustomMovementMode) {
		case CUSTOM_Jetpack:
			ShooterCharacterOwner->Jetpack1P->PhysJetpack(deltaTime, Iterations);
			break;
		default:
			break;
	}
}

FNetworkPredictionData_Client_Shooter::FNetworkPredictionData_Client_Shooter(const UCharacterMovementComponent& ClientMovement)
	: Super(ClientMovement)
{

}

FSavedMovePtr FNetworkPredictionData_Client_Shooter::AllocateNewMove() {
	return FSavedMovePtr(new FSavedMove_ShooterCharacter());
}

void FSavedMove_ShooterCharacter::Clear() {
	Super::Clear();
	savedUseJetpack = false;
}

void FSavedMove_ShooterCharacter::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) {
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);
	const AShooterCharacter* ShooterCharacterOwner = Cast<AShooterCharacter>(Character);
	if (ShooterCharacterOwner)
		savedUseJetpack = ShooterCharacterOwner->Jetpack1P->bUseJetpack;
}

void FSavedMove_ShooterCharacter::PrepMoveFor(ACharacter* Character) {
	Super::PrepMoveFor(Character);

	const AShooterCharacter* ShooterCharacterOwner = Cast<AShooterCharacter>(Character);
	if (ShooterCharacterOwner)
		ShooterCharacterOwner->Jetpack1P->ExecJetpack(savedUseJetpack);
}
