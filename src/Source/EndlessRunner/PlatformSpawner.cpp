// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformSpawner.h"
#include "Obstacle.h"
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
	obstacles = {};
}

// Called every frame
void APlatformSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (spawnCooldown -= DeltaTime; spawnCooldown < 0; spawnCooldown += spawndelay)
	{
		float currentSpeed = (!gamemode ? 100: gamemode->obstacleSpeed );
		SpawnPlatform(
			FVector(
				0, 
				distanceBetweenLanes * (FMath::RandRange(0, numberOfLanes) - numberOfLanes / 2), 
				10),
			currentSpeed + FMath::FRandRange(0.f, 10.f)
		);
		

	}
}

AObstacle* APlatformSpawner::SpawnPlatform(const FVector& position, float speed)
{
	auto* world = GetWorld();
	if (!world) return nullptr;
	AObstacle* spawned = (AObstacle*) world->SpawnActor(AObstacle::StaticClass());
	spawned->Set(speed, 1100, FVector{ -1, 0, 0 },this);
	spawned->SetActorLocation(position);
	obstacles.Add(spawned);
	return spawned;
}

void APlatformSpawner::PlatformExpiered(AObstacle* child)
{
	obstacles.Remove(child);
}

void APlatformSpawner::ExplodeRandomObstacle()
{
	auto obstacle = obstacles[FMath::Rand() % obstacles.Num()];
	DrawDebugSphere(GetWorld(), obstacle->GetActorLocation(), 100, 20, FColor::Orange, false, 2);
	obstacle->Destroy();
}

