// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/ShooterDamageType.h"
#include "ShooterFreezingDamageType.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UShooterFreezingDamageType : public UShooterDamageType
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float FreezingTime;
};
