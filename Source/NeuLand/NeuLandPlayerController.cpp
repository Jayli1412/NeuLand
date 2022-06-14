// Fill out your copyright notice in the Description page of Project Settings.


#include "NeuLandPlayerController.h"

#include "HUDWidget.h"
#include "Blueprint/UserWidget.h"

void ANeuLandPlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (BP_HUDWidget != nullptr)
    {
        // UUserWidget* uWidget = CreateWidget(this, BP_HUDWidget);
        HUDWidget = CreateWidget<UHUDWidget>(this, BP_HUDWidget);
        HUDWidget->AddToViewport();
    }
}

void ANeuLandPlayerController::UpdateHealthPercent(float HealthPercent)
{
    if (HUDWidget != nullptr)
    {
        HUDWidget->UpdateHealthPercent(HealthPercent);
    }
}

void ANeuLandPlayerController::ShowHUDWidget()
{
    if (BP_HUDWidget != nullptr)
    {
        HUDWidget = CreateWidget<UHUDWidget>(this, BP_HUDWidget);
        HUDWidget->AddToViewport();
    }
}