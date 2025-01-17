// Fill out your copyright notice in the Description page of Project Settings.


#include "ExPraoThrower.h"
#include "Engine/World.h"
#include "NeuLandFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "StoneProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AExPraoThrower::AExPraoThrower()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LookAtActorComponent = CreateDefaultSubobject<ULookAtActorComponent>(TEXT("Look At Actor Component"));
	LookAtActorComponent->SetupAttachment(RootComponent);

	ThrowSource = CreateDefaultSubobject<USceneComponent>(TEXT("Throw Source"));
	ThrowSource->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AExPraoThrower::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	LookAtActorComponent->SetTarget(PlayerCharacter);

}

// Called every frame
void AExPraoThrower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bCanSeePlayer = LookAtActorComponent->CanSeeTarget();

	ThrowRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation());

	if (bCanSeePlayer != bPreviousCanSeePlayer)
	{
		if (bCanSeePlayer)
		{
			if (UKismetMathLibrary::Abs((GetActorLocation() - UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation()).Size()) < 1000.f)
			{
				GetWorldTimerManager().SetTimer(ThrowTimerHandle, this, &AExPraoThrower::ThrowStone, ThrowingInterval, true, ThrowingDelay);
			}
			else
			{
				GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
			}
		}
		else
		{
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}
	bPreviousCanSeePlayer = LookAtActorComponent->CanSeeTarget();

}

// Called to bind functionality to input
void AExPraoThrower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AExPraoThrower::CanSeeActor(const AActor* TargetActor) const
{
	if (TargetActor == nullptr)
	{
		return false;
	}

	// Save the result of the line trace
	FHitResult Hit;

	// The position of line trace's start, end
	FVector Start = LookAtActorComponent->GetComponentLocation();
	FVector End = TargetActor->GetActorLocation();

	FQuat Rotation = FQuat::Identity;

	// Trace channel to use
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel5;

	FCollisionQueryParams QueryParams;
	FCollisionShape Shape = FCollisionShape::MakeSphere(20.f);

	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(TargetActor);

	// Run the line trace
	// GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);
	GetWorld()->SweepSingleByChannel(Hit, Start, End, Rotation, Channel, Shape, QueryParams);

	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	return !Hit.bBlockingHit;
}

void AExPraoThrower::ThrowStone()
{
	if (StoneClass == nullptr)
	{
		return;
	}

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.f;
	float X, Y, Z = 0;
	UKismetMathLibrary::BreakRotator(ThrowRotation, X, Y, Z);
	FVector SpawnLocation = ThrowSource->GetComponentLocation() + (ForwardVector * SpawnDistance);
	FTransform SpawnTransform(UKismetMathLibrary::MakeRotator(X, Y + 10.f, Z), SpawnLocation);

	// spawn new stone
	AStoneProjectile* Projectile = GetWorld()->SpawnActorDeferred<AStoneProjectile>(StoneClass, SpawnTransform);
	Projectile->GetProjectileMovementComponent()->InitialSpeed = 1000.f;
	Projectile->FinishSpawning(SpawnTransform);
}