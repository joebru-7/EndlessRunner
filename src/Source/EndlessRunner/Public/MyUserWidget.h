// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndlessRunnerConfig.h"
#include "MyUserWidget.generated.h"


/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UMyUserWidget (const FObjectInitializer& ObjectInitializer) :UUserWidget( ObjectInitializer){}

	UPROPERTY(BlueprintReadOnly)
	int health; // managed from gamemode

	UPROPERTY(BlueprintReadOnly)
	int score; // managed from gamemode

	UE_NODISCARD UFUNCTION(BlueprintCallable)
	FString readHighscore();

	UFUNCTION(BlueprintImplementableEvent)
	void updatehiscoreDisplay();
};
