// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class ENDLESSRUNNER_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	friend class APlatformSpawner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector direction = FVector(1, 0, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float distance = 10000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed = 10;

	FVector startpos;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComp;
};