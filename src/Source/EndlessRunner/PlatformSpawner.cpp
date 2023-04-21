// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformSpawner.h"
#include "MovingPlatform.h"

// Sets default values
APlatformSpawner::APlatformSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	for (spawnCooldown -= DeltaTime; spawnCooldown < 0; spawnCooldown += spawndelay)
	{
		auto spawned = GetWorld()->SpawnActor<AMovingPlatform>();
		spawned->speed = 100 + FMath::FRandRange(0, 100);
		spawned->direction = FVector(1, 0, 0);
		spawned->SetActorLocation(GetActorLocation() + FVector(0, FMath::RandRange(-spawnRadius, spawnRadius), 0));
	}
}

