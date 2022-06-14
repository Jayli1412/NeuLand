// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HealthComponent.h"
#include "HealthInterface.h"
#include "HoeRootCharacter.generated.h"

UCLASS()
class NEULAND_API AHoeRootCharacter : public ACharacter, public IHealthInterface
{
	GENERATED_BODY()

private:
	class UHealthComponent* HealthComponent;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "CharacterMovement")
		float ZoomSensitivity = 10.f;

	UPROPERTY(BlueprintReadWrite, Category = "CharacterMovement")
		float ZoomMin = 100.f;

	UPROPERTY(BlueprintReadWrite, Category = "CharacterMovement")
		float ZoomMax = 300.f;

	UPROPERTY(BlueprintReadWrite, Category = "CharacterMovement")
		float SprintWalkSpeed = 600.f;

	UPROPERTY(BlueprintReadWrite, Category = "CharacterMovement")
		float WalkSpeed = 300.f;

	UPROPERTY(BlueprintReadWrite, Category = "CharacterMovement")
		float SpeedMultiplier = 1.f;

public:
	// Sets default values for this character's properties
	AHoeRootCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "hdb", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "hdb", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnDeath_Implementation() override;
	virtual void OnTakeDamage_Implementation() override;

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveRight(float Value);
	void MoveForward(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	void TouchBegin(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchEnd(ETouchIndex::Type FingerIndex, FVector Location);

	void CameraZoomIn();
	void CameraZoomOut();

	void Walk();
	void Sprint();

};
