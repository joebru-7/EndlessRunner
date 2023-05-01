// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"


/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	int health = 3; //TODO make read

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthDisplay();
};
