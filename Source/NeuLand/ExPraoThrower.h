// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ExPraoThrower.generated.h"

UCLASS()
class NEULAND_API AExPraoThrower : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExPraoThrower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Changes the character's rotation to look at passed actor
	void LookAtActor(AActor* TargetActor);

	// Check if can see the passed actor
	bool CanSeeActor(const AActor* TargetActor) const;
};
