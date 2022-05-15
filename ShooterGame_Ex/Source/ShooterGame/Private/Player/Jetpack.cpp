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

	RecoverJetpackFuel(DeltaTime);
	// ...
}

bool UJetpack::CanUse() { 
	return Fuel > 0;
}

void UJetpack::RecoverJetpackFuel(float DeltaTime) {
	if (!bUseJetpack) {
		float FuelRecovered = FuelRecover * (DeltaTime * TimeRecover);
		Fuel = FMath::Clamp(Fuel + FuelRecover, 0.0f, MaxFuel);
	}
}

void UJetpack::PhysJetpack(float deltaTime, int32 Iterations) {
	float JetDir = CharacterMovement->GetGravityZ() * -1;

	float FuelConsumed = FuelConsume * (deltaTime / TimeFuelConsume);
	Fuel = FMath::Clamp(Fuel - FuelConsumed, 0.0f, MaxFuel);

	if (Fuel <= 0.0f) {
		bUseJetpack = false;
		CharacterMovement->SetMovementMode(EMovementMode::MOVE_Falling);
	}

	ElapsedTime += deltaTime * JetDir;
	float CurveValue = JetpackCurve->GetFloatValue(ElapsedTime);

	CharacterMovement->Velocity.Z = CurveValue * MaxSpeed * deltaTime;

	CharacterMovement->PhysFalling(deltaTime, Iterations);
}

void UJetpack::SetJetpack(bool useRequest) {
	if (!GetOwner()->HasAuthority() && ShooterCharacterOwner->IsLocallyControlled())
		ServerJetpack(useRequest);
	else
		ExecJetpack(useRequest);
}

void UJetpack::ExecJetpack(bool useRequest) {
	if (CanUse()) {
		if (useRequest) {
			bUseJetpack = true;
			CharacterMovement->SetMovementMode(EMovementMode::MOVE_Custom, ECustomMovementMode::CUSTOM_Jetpack);
		}
	}

	if (!useRequest) {
		bUseJetpack = false;
		CharacterMovement->SetMovementMode(EMovementMode::MOVE_Falling);
	}
}

bool UJetpack::ServerJetpack_Validate(bool useRequest) {
	return true;
}

void UJetpack::ServerJetpack_Implementation(bool useRequest) {
	if (CanUse())
		ExecJetpack(useRequest);
	else if (!useRequest)
		ExecJetpack(useRequest);
}

