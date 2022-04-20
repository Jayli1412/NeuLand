// Fill out your copyright notice in the Description page of Project Settings.


#include "ExPraoGuardController.h"

AExPraoGuardController::AExPraoGuardController()
{
	SetGenericTeamId(1);
}

ETeamAttitude::Type AExPraoGuardController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other))
	{
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
		}
	}
	return ETeamAttitude::Neutral;
}
