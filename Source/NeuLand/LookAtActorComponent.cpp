// Fill out your copyright notice in the Description page of Project Settings.


#include "LookAtActorComponent.h"

#include "ExPraoThrower.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "NeuLandFunctionLibrary.h"

// Sets default values for this component's properties
ULookAtActorComponent::ULookAtActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULookAtActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void ULookAtActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	bCanSeeTarget = LookAtActor();

	// ...
}

bool ULookAtActorComponent::LookAtActor()
{
	if (TargetActor == nullptr) return false;

	TArray<const AActor*> IgnoreActors = { GetOwner(),TargetActor };
	if (UNeuLandFunctionLibrary::CanSeeActor(GetWorld(), GetComponentLocation(), TargetActor, IgnoreActors))
	{
		FVector Start = Start = GetOwner()->GetActorLocation();
		FVector End = TargetActor->GetActorLocation();
		// Caculate the necessary rotation for the Start point to face the End point
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);
		float X, Y, Z = 0;
		UKismetMathLibrary::BreakRotator(LookAtRotation, X, Y, Z);
		FRotator LookAtRotationZeroPitch = UKismetMathLibrary::MakeRotator(X, 0, Z);

		//Set the enemy's rotation to that rotation
		GetOwner()->SetActorRotation(LookAtRotationZeroPitch);
		FRotator ThrowSourceRotation;
		if (AExPraoThrower* Owner = Cast<AExPraoThrower>(GetOwner()))
		{
			Owner->ThrowSource->SetWorldRotation(LookAtRotation);
			ThrowSourceRotation = Owner->ThrowSource->GetComponentRotation() - LookAtRotationZeroPitch;
		}
		// GetOwner()->ThrowSource->SetWorldRotation(LookAtRotation);
		FRotator ThrowPitch = ThrowSourceRotation - LookAtRotationZeroPitch;
		SetWorldRotation(ThrowPitch, false, nullptr, ETeleportType::None);
		return true;
	}
	return false;
}