// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ExPraoGuardController.generated.h"

/**
 * 
 */
UCLASS()
class NEULAND_API AExPraoGuardController : public AAIController
{
	GENERATED_BODY()
		AExPraoGuardController();

public:
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
};
