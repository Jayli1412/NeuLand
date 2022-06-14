// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HUDWidget.h"

#include "NeuLandPlayerController.generated.h"

/**
 *
 */
UCLASS()
class NEULAND_API ANeuLandPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UHUDWidget* HUDWidget;

protected:
	virtual void BeginPlay() override;


public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UHUDWidget> BP_HUDWidget;

	void ShowHUDWidget();

	void UpdateHealthPercent(float HealthPercent);
};
