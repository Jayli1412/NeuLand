// Fill out your copyright notice in the Description page of Project Settings.


#include "NeuLandFunctionLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"


bool UNeuLandFunctionLibrary::CanSeeActor(const UWorld* World, FVector Location, const AActor* TargetActor, TArray<const AActor*> IgnoreActors)
{
    if (TargetActor == nullptr)
    {
        return false;
    }

    // Save the result of the line trace
    FHitResult Hit;

    // The position of line trace's start, end
    FVector Start = Location;
    FVector End = TargetActor->GetActorLocation();

    FQuat Rotation = FQuat::Identity;

    // Trace channel to use
    ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel5;

    FCollisionQueryParams QueryParams;
    FCollisionShape Shape = FCollisionShape::MakeSphere(20.f);

    QueryParams.AddIgnoredActors(IgnoreActors);

    // Run the line trace
    // GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);
    World->SweepSingleByChannel(Hit, Start, End, Rotation, Channel, Shape, QueryParams);

    DrawDebugLine(World, Start, End, FColor::Red);

    return !Hit.bBlockingHit;
}