// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterGame.h"
#include "Player/Jetpack.h"

// Sets default values for this component's properties
UJetpack::UJetpack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UJetpack::BeginPlay()
{
	Super::BeginPlay();

	ShooterCharacterOwner = Cast<AShooterCharacter>(GetOwner());
	CharacterMovement = ShooterCharacterOwner->GetCharacterMovement();
	// ...
	
}


// Called every frame
void UJetpack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UJetpack::PhysJetpack(float deltaTime, int32 Iterations) {
	float JetDir = CharacterMovement->GetGravityZ() * -1;

	float FuelConsumed = FuelConsume * (deltaTime / TimeFuelConsume);
	Fuel = FMath::Clamp(Fuel - FuelConsumed, 0.0f, MaxFuel);

	if (Fuel <= 0.0f) {
		CharacterMovement->SetMovementMode(EMovementMode::MOVE_Falling);
	}

	ElapsedTime += deltaTime * JetDir;
	float CurveValue = JetpackCurve->GetFloatValue(ElapsedTime);

	CharacterMovement->Velocity.Z = CurveValue * MaxSpeed * deltaTime;

	CharacterMovement->PhysFalling(deltaTime, Iterations);
}

