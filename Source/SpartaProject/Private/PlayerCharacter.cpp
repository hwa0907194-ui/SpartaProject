// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetCapsuleSize(50, 50);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->TargetArmLength = 100;
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->bInheritPitch = true;
	SpringArmComponent->bInheritYaw = true;
	SpringArmComponent->bInheritRoll = true;
	SpringArmComponent->SetUsingAbsoluteRotation(false);


	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT( "CameraComponent"));
	CameraComponent->bUsePawnControlRotation = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetRelativeLocation(FVector(0, 0, -25));


	RootComponent = CapsuleComponent;

	SkeletalMeshComponent ->SetupAttachment(RootComponent);
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	SpringArmComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr)
	{	
		ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

		if (Subsystem != nullptr)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(
			Move,
			ETriggerEvent::Triggered,
			this,
			&APlayerCharacter::MoveInput
		);

		EnhancedInputComponent->BindAction(
			Look,
			ETriggerEvent::Triggered,
			this,
			&APlayerCharacter::LookInput
		);
	}
}


void APlayerCharacter::MoveInput(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	float DeltaTime = GetWorld()->GetDeltaSeconds();

	FRotator CameraRotation = CameraComponent->GetComponentRotation();

	FRotator YawRotation(
		0.0f,
		CameraRotation.Yaw,
		0.0f
	);

	FVector Forward = GetActorForwardVector();
	FVector Right = GetActorRightVector();


	Forward.Normalize();
	Right.Normalize();

	FVector MoveDirection =
		Forward * InputValue.Y +
		Right * InputValue.X;


	AddActorWorldOffset(MoveDirection * MoveSpeed * DeltaTime, true);
}

void APlayerCharacter::LookInput(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	float DeltaTime = GetWorld()->GetDeltaSeconds();

	AddActorLocalRotation(
		FRotator(
			InputValue.Y * LookSpeed * DeltaTime,
			InputValue.X * LookSpeed * DeltaTime,
			0.0f
		)
	);
}