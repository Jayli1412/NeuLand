// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LookAtActorComponent.h"
#include "Math/UnrealMathUtility.h"
#include "TimerManager.h"

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
	// can see player ?
	bool bCanSeePlayer = false;
	// could see player at last frame ?
	bool bPreviousCanSeePlayer = false;

	FTimerHandle ThrowTimerHandle;
	float ThrowingInterval = FMath::RandRange(1.0f, 2.0f);
	float ThrowingDelay = FMath::RandRange(0.f, 1.5f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Look At", meta = (AllowPrivateAccess = "true"))
		class ULookAtActorComponent* LookAtActorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Look At", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* ThrowSource;

	FRotator ThrowRotation;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Check if can see the passed actor
	bool CanSeeActor(const AActor* TargetActor) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StoneProjectile")
		TSubclassOf<class AStoneProjectile> StoneClass;


	UFUNCTION()
		void ThrowStone();
};
