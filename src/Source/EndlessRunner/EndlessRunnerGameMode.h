// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerConfig.h"
#include "EndlessRunnerGameMode.generated.h"

UCLASS(minimalapi)
class AEndlessRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEndlessRunnerGameMode();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float currentSpeed;

	int score = 0;
	int playerhealth = startingHealth;

	UPROPERTY(VisibleAnywhere)
	class UMyUserWidget* HudWidget;

	virtual void RestartPlayer(AController* player) override;

	ConstructorHelpers::FClassFinder<UMyUserWidget>* widget;

	//positive extr lives healing
	void updateHealth(int amount);

};



