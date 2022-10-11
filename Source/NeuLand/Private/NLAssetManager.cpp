// Fill out your copyright notice in the Description page of Project Settings.


#include "NLAssetManager.h"
#include "AbilitySystemGlobals.h"

void UNLAssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();
    // UAbilitySystemGlobals::Get().InitGlobalData();
    UE_LOG(LogTemp, Warning, TEXT("Hello World!"));
}