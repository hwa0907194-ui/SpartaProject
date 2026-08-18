// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;

UCLASS()
class SPARTAPROJECT_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UCapsuleComponent* CapsuleComponent;
	USkeletalMeshComponent* SkeletalMeshComponent;
	USpringArmComponent* SpringArmComponent;
	UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere)
	UInputAction* Move;
	UPROPERTY(EditAnywhere)
	UInputAction* Look;
	UPROPERTY(EditAnywhere)
	UInputMappingContext* InputMappingContext;


	UPROPERTY(EditAnywhere)
	float MoveSpeed = 300.0f;

	UPROPERTY(EditAnywhere)
	float LookSpeed = 100.0f;

	void MoveInput(const FInputActionValue& Value);
	void LookInput(const FInputActionValue& Value);



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
