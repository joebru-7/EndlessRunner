// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "EndlessRunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "PlatformSpawner.h"
#include "MyUserWidget.h"

#define MY_LOG(format,...) UE_LOG(LogTemp, Warning, TEXT(format), __VA_ARGS__)

AEndlessRunnerGameMode::AEndlessRunnerGameMode():currentSpeed(50)
{
	PrimaryActorTick.bCanEverTick = true;
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}


	static ConstructorHelpers::FClassFinder<UMyUserWidget> static_widget(TEXT("/Game/HUD"));
	widget = &static_widget;

}

void AEndlessRunnerGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentSpeed += DeltaTime;

	score += 1;
	HudWidget->score = score;


	//MY_LOG("TEST");
}

void AEndlessRunnerGameMode::BeginPlay()
{
	Super::BeginPlay();

	//create hud after instance is valid
	if (!HudWidget || !HudWidget->IsValidLowLevel())
	{
		static int health = 6;
		HudWidget = Cast<UMyUserWidget>(CreateWidget(GetGameInstance(), widget->Class));
		if (HudWidget)
		{
			HudWidget->AddToViewport();
			HudWidget->health = health;
		}
	}
}

void AEndlessRunnerGameMode::RestartPlayer(AController* player)
{
	Super::RestartPlayer(player);
	
	static APlatformSpawner* spawner = nullptr;
	if (spawner == nullptr || !spawner->IsValidLowLevel())
	{
		spawner = Cast<APlatformSpawner>(UGameplayStatics::GetActorOfClass(this, APlatformSpawner::StaticClass()));
	}

	FVector location = player->GetPawn()->GetActorLocation();
	location.Z = 200;
	player->GetPawn()->SetActorLocation(location);
	location.Z = 1;

	AActor* spawned = spawner->SpawnPlatform(location,0);
	spawned->SetLifeSpan(10);
}
