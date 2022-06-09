// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/ShooterDamageType.h"
#include "ShooterShrinkDamageType.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UShooterShrinkDamageType : public UShooterDamageType
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shrink")
	float ShrinkTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shrink")
	float ResizeTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shrink")
	FVector ShrinkScale;
};
