// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

#include "Item2.generated.h"

UCLASS()
class SPARTAPROJECT_API AItem2 : public AActor
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	AItem2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float RotationSpeed = 90.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
