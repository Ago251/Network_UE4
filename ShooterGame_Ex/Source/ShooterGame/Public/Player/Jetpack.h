// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "Engine/EngineTypes.h"
#include "Jetpack.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API UJetpack : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJetpack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability|Jetpack")
	UCurveFloat* JetpackCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuel")
	float MaxFuel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuel")
	float FuelRecover;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuel")
	float FuelConsume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuel")
	float TimeFuelConsume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuel")
	float TimeRecover;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "Fuel")
	bool bUseJetpack;

private:
	float Fuel;
	float ElapsedTime;
	AShooterCharacter* ShooterCharacterOwner;
	UCharacterMovementComponent* CharacterMovement;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	const float& GetFuel() const { return Fuel; }

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool CanUse();

	void RecoverJetpackFuel(float DeltaTime);

	void ConsumeJetpackFuel(float DeltaTime);

	void SetJetpack(bool useRequest);

	void PhysJetpack(float deltaTime, int32 Iterations);

	void ExecJetpack(bool useRequest);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void ServerJetpack(bool useRequest);
};
