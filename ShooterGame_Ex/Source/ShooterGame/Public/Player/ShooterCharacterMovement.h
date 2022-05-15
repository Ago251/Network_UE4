// Copyright Epic Games, Inc. All Rights Reserved.

/**
 * Movement component meant for use with Pawns.
 */

#pragma once
#include "ShooterCharacterMovement.generated.h"

UENUM(BlueprintType)
enum ECustomMovementMode
{
	CUSTOM_Jetpack = 0
};

UCLASS()
class UShooterCharacterMovement : public UCharacterMovementComponent
{
	GENERATED_UCLASS_BODY()

	virtual float GetMaxSpeed() const override;

	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
};


/** represents a saved move on the client that has been sent to the server and might need
to be played back. */
class FSavedMove_ShooterCharacter : public FSavedMove_Character
{

	friend class UShooterCharacterMovement;

public:
	typedef FSavedMove_Character Super;
	/** Clear saved move properties, so it can be re-used. */
	virtual void Clear() override;
	/** Called to set up this saved move (when initially created) to make a predictive correction. */
	virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData) override;

	/** Called before ClientUpdatePosition uses this SavedMove to make a predictive correction */
	virtual void PrepMoveFor(ACharacter* Character) override;

	bool savedUseJetpack = false;
};

/** Network data representation on the client. */
class FNetworkPredictionData_Client_Shooter : public FNetworkPredictionData_Client_Character
{
public:
	FNetworkPredictionData_Client_Shooter(const UCharacterMovementComponent& ClientMovement);
	typedef FNetworkPredictionData_Client_Character Super;
	virtual FSavedMovePtr AllocateNewMove() override;
};

