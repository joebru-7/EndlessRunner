// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MovingPlatform.h"
#include "Obstacle.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AObstacle : public AMovingPlatform
{
	GENERATED_BODY()
public:
	AObstacle();
	
	UFUNCTION()
	void OnCollision( UPrimitiveComponent* OtherComponent, AActor* OtherActor, UPrimitiveComponent* x, int32 y, bool z, const FHitResult& Hit);

	virtual void BeginPlay() override;
};
