// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "EndlessRunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "PlatformSpawner.h"
#include "MyUserWidget.h"
#include <fstream>
#include "EndlessRunnerConfig.h"

AEndlessRunnerGameMode::AEndlessRunnerGameMode():currentSpeed(50),obstacleSpeed(200)
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
	obstacleSpeed += DeltaTime;

	++score;
	if(HudWidget)
	HudWidget->score = score;

}

void AEndlessRunnerGameMode::BeginPlay()
{
	Super::BeginPlay();

	//create hud after instance is valid
	if (!HudWidget || !HudWidget->IsValidLowLevel())
	{
		HudWidget = Cast<UMyUserWidget>(CreateWidget(GetGameInstance(), widget->Class));
		if (HudWidget)
		{
			HudWidget->AddToViewport();
			HudWidget->health = playerhealth;
		}
	}
}

void writeHighscore(int score)
{

	std::fstream highsoreFIle;
	highsoreFIle.open("C:\\temp\\Highscore.txt");

	//read higscore into array (no error checking)
	TArray<int> scores{};
	scores.Add(score);
	if (highsoreFIle.is_open()) {
		while (!highsoreFIle.eof())
		{
			int x;
			highsoreFIle >> x;
			scores.Add(x);
		}
	}
	highsoreFIle.close();
	if (scores.Num() < 5)
	{
		scores.AddDefaulted(5 - scores.Num());
	}


	// put in order
	scores.Sort(std::greater<int>());

	//write back to file
	highsoreFIle.open("C:\\temp\\Highscore.txt", std::ios::out);
	for (int i = 0; i < 5; i++)
	{
		highsoreFIle << scores[i] << '\n';
	}
	highsoreFIle << "                       \0"; // make sure file is long enugh to cover default text
	highsoreFIle.close();
}

void AEndlessRunnerGameMode::updateHealth(int amount)
{
	playerhealth += amount;
	HudWidget->health = playerhealth;

	if (playerhealth == 0)
	{
		writeHighscore(score);
		HudWidget->updatehiscoreDisplay();
		playerhealth = HudWidget->health = 3;
		score = HudWidget->score = 0;
		currentSpeed = startSpeed;
	}
}

void AEndlessRunnerGameMode::RestartPlayer(AController* player)
{
	Super::RestartPlayer(player);
	
	static APlatformSpawner* spawner = nullptr;
	if (spawner == nullptr || !spawner->IsValidLowLevel())
	{
		TArray<AActor*> founds{};
		UGameplayStatics::GetAllActorsOfClass(this, APlatformSpawner::StaticClass(), founds);
		for (auto var : founds)
		{
			if (Cast<APlatformSpawner>(var) && !Cast<APlatformSpawner>(var)->isSpawningObstacles) {
				spawner = Cast<APlatformSpawner>(var);
				break;
			}
		}
	}

	FVector location = player->GetPawn()->GetActorLocation();
	location.Z = 200;
	player->GetPawn()->SetActorLocation(location);
	location.Z = 1;

	AActor* spawned = spawner->SpawnPlatform(location,0);
	spawned->SetLifeSpan(10);
}
