// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector direction = FVector(1, 0, 0);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float distance = 10000;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float speed = 10;

	FVector startpos;

public: 
	void SetSpeed(float newSpeed) { speed = newSpeed;updateLifetime(); }
	void SetDistance(float newDistance) { distance = newDistance; updateLifetime(); }
	void SetDirection(FVector newDirection) { direction = newDirection; updateLifetime(); }
	void Set(float newSpeed, float newDistance, FVector newDirection)
	{
		speed = newSpeed; distance = newDistance; direction = newDirection;
		updateLifetime();
	}
private:
	void updateLifetime();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComp;
};
*/
