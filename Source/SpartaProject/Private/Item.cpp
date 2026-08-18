// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	RootComponent = StaticMeshComp;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation.X += MoveSpeed * DeltaTime * MoveDirection;
	SetActorLocation(CurrentLocation);

	if (CurrentLocation.X - StartLocation.X >= MaxRange)
	{
		MoveDirection = -1.0f;
	}

	if (CurrentLocation.X <= StartLocation.X)
	{
		MoveDirection = 1.0f;
	}
}

