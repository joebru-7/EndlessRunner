// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformSpawner.h"
#include "MovingPlatform.h"
#include "EndlessRunnerGameMode.h"

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
	gamemode = Cast<AEndlessRunnerGameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void APlatformSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (spawnCooldown -= DeltaTime; spawnCooldown < 0; spawnCooldown += spawndelay)
	{
		float currentSpeed = (gamemode ? gamemode->currentSpeed : 100);
		SpawnPlatform(
			FVector(0, distanceBetweenLanes * (FMath::RandRange(0, numberOfLanes) - numberOfLanes / 2), 0),
			currentSpeed + FMath::FRandRange(0.f, 10.f)
		);
	}
}

AActor* APlatformSpawner::SpawnPlatform(const FVector& position, float speed) const
{
	AMovingPlatform* spawned = GetWorld()->SpawnActor<AMovingPlatform>();
	spawned->speed = speed;
	spawned->direction = FVector(1, 0, 0);
	spawned->SetActorLocation(position);
	return (AActor*) spawned;
}

