// Fill out your copyright notice in the Description page of Project Settings.


#include "HoeRootCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NeuLandPlayerController.h"

// Sets default values
AHoeRootCharacter::AHoeRootCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Instantiating class components
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;


	//Attaching springarm component to the default character's skeletal mesh component
	CameraBoom->SetupAttachment(Cast<USceneComponent>(GetCapsuleComponent()));

	// Attaching camera component to the springarm component
	// CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	// CameraComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);

	// Setting default properties of the SpringArmComp
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->TargetArmLength = 300.f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void AHoeRootCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = SpeedMultiplier * WalkSpeed;

}

// Called every frame
void AHoeRootCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHoeRootCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHoeRootCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &AHoeRootCharacter::MoveForward);
	// PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn", this, &AHoeRootCharacter::Turn);
	// PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AHoeRootCharacter::LookUp);
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AHoeRootCharacter::TouchBegin);
	PlayerInputComponent->BindTouch(IE_Released, this, &AHoeRootCharacter::TouchEnd);
	PlayerInputComponent->BindAction("Camera ZoomIn", IE_Pressed, this, &AHoeRootCharacter::CameraZoomIn);
	PlayerInputComponent->BindAction("Camera ZoomOut", IE_Pressed, this, &AHoeRootCharacter::CameraZoomOut);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AHoeRootCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AHoeRootCharacter::Walk);
}

void AHoeRootCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
		const FVector Direction = UKismetMathLibrary::GetRightVector(YawRotation);
		AddMovementInput(Direction, Value);
	}
}

void AHoeRootCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
		const FVector Direction = UKismetMathLibrary::GetForwardVector(YawRotation);
		AddMovementInput(Direction, Value);
	}
}

void AHoeRootCharacter::Turn(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		AddControllerYawInput(UKismetMathLibrary::FClamp(Value, -2.f, 2.f));
	}
}

void AHoeRootCharacter::LookUp(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		AddControllerPitchInput(UKismetMathLibrary::FClamp(Value, -2.f, 2.f));
	}
}

void AHoeRootCharacter::TouchBegin(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AHoeRootCharacter::TouchEnd(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AHoeRootCharacter::CameraZoomIn()
{
	if (Controller)
	{
		float PreviousLength = CameraBoom->TargetArmLength;
		CameraBoom->TargetArmLength = UKismetMathLibrary::FClamp((-1.f * ZoomSensitivity) + PreviousLength, ZoomMin, ZoomMax);
	}

}

void AHoeRootCharacter::CameraZoomOut()
{
	if (Controller)
	{
		float PreviousLength = CameraBoom->TargetArmLength;
		CameraBoom->TargetArmLength = UKismetMathLibrary::FClamp((1.f * ZoomSensitivity) + PreviousLength, ZoomMin, ZoomMax);
	}

}

void AHoeRootCharacter::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed * SpeedMultiplier;
}

void AHoeRootCharacter::Sprint()
{

	GetCharacterMovement()->MaxWalkSpeed = SprintWalkSpeed * SpeedMultiplier;
}

void AHoeRootCharacter::OnDeath_Implementation()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

void AHoeRootCharacter::OnTakeDamage_Implementation()
{
	ANeuLandPlayerController* PlayerController = Cast<ANeuLandPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->UpdateHealthPercent(HealthComponent->GetHealthPercent());
	}
}