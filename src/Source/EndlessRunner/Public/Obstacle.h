// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MovingPlatform.h"
#include "Obstacle.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AObstacle : public AActor
{
	GENERATED_BODY()
public:
	AObstacle();
	
	UFUNCTION()
	void OnCollision( UPrimitiveComponent* OtherComponent, AActor* OtherActor, UPrimitiveComponent* x, int32 y, bool z, const FHitResult& Hit);

	virtual void BeginPlay() override;

	virtual void LifeSpanExpired() override;
	virtual void Destroyed() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector direction = FVector(1, 0, 0);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float distance = 10000;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float speed = 10;
	FVector startpos;
	class APlatformSpawner* parent;

public:
	void SetSpeed(float newSpeed) { speed = newSpeed; updateLifetime(); }
	void SetDistance(float newDistance) { distance = newDistance; updateLifetime(); }
	void SetDirection(FVector newDirection) { direction = newDirection; updateLifetime(); }
	void SetParent(APlatformSpawner* newParent) { parent = newParent; };
	void Set(float newSpeed, float newDistance, FVector newDirection, APlatformSpawner* newParent)
	{
		speed = newSpeed; distance = newDistance; direction = newDirection; parent = newParent;
		updateLifetime();
	}


private:
	void updateLifetime();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComp;
};
