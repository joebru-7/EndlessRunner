// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawner.generated.h"

UCLASS()
class ENDLESSRUNNER_API APlatformSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class AMovingPlatform* platform;

	UPROPERTY(EditAnywhere,meta=(ClampMin = 0.01f, ClampMax=10))
	float spawndelay = 1;
	float spawnCooldown = 0;

	UPROPERTY(EditAnywhere)
	float spawnRadius = 100;
};
