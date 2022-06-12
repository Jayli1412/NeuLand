// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneProjectile.h"
#include "Components/SphereComponent.h"
#include "HoeRootCharacter.h"
#include "HealthComponent.h"
#include "Math/Vector.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AStoneProjectile::AStoneProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereComponent->SetSphereRadius(10.f);
	SphereComponent->SetCollisionProfileName(FName("StoneProjectile"));
	SphereComponent->SetSimulatePhysics(true);

	// make actor to call onhit event
	SphereComponent->SetNotifyRigidBodyCollision(true);
	SphereComponent->OnComponentHit.AddDynamic(this, &AStoneProjectile::OnHit);

	RootComponent = SphereComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

}

// Called when the game starts or when spawned
void AStoneProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(3.f);
}

// Called every frame
void AStoneProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStoneProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AHoeRootCharacter* Player = Cast<AHoeRootCharacter>(OtherActor);
	if (Player != nullptr)
	{
		UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();
		if (HealthComponent != nullptr)
		{
			float X, Y, Z = 0.f;
			UKismetMathLibrary::BreakVector(GetVelocity(), X, Y, Z);
			UKismetMathLibrary::FClamp(X, -1.f, 1.f);
			UKismetMathLibrary::FClamp(Y, -1.f, 1.f);
			float ForceMultiplier = 0.1f;
			FVector LaunchForce = FVector(X, Y, 100.f / ForceMultiplier) * KnockBackAmount * ForceMultiplier;
			Player->LaunchCharacter(LaunchForce, true, true);
			// HealthComponent->LoseHealth(Damage);
		}
		Destroy();
	}
}